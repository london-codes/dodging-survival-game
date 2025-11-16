#include "PlayerShip.h"


PlayerShip::PlayerShip()
    : texture("assets/playership.png"), visual(texture),
    exhaustVisual(texture) // sf::Sprite has not default constructor so it needs to be initializer list with dummy texture
{
    // For Both the HitBox and Visual I think the origin of rotaiton might need to be adjusted so that it matches how it moves better.

    // HitBox
    hitBox.setPointCount(8);
    hitBox.setPoint(0, sf::Vector2f{ -7, -20 });
    hitBox.setPoint(1, sf::Vector2f{ 7, -20 });
    hitBox.setPoint(2, sf::Vector2f{ 7, 10 });
    hitBox.setPoint(3, sf::Vector2f{ 15, 10 });
    hitBox.setPoint(4, sf::Vector2f{ 15, 22 });
    hitBox.setPoint(5, sf::Vector2f{ -15, 22 });
    hitBox.setPoint(6, sf::Vector2f{ -15, 10 });
    hitBox.setPoint(7, sf::Vector2f{ -7, 10 });
    hitBox.setPosition({ 800.f,450.f });

    //Ship visuals
    visual.setScale({ 1.f, 1.f });
    visual.setOrigin({ visual.getLocalBounds().size.x / 2, visual.getLocalBounds().size.y / 2 });
    visual.setPosition({ 800.f,450.f });

    // Thruster Visual
    if (!exhaustAnimation[0].loadFromFile("assets/flame1.png"))
        std::cerr << "Failed to load assets/flame1.png\n";
    if (!exhaustAnimation[1].loadFromFile("assets/flame2.png"))
        std::cerr << "Failed to load assets/flame2.png\n";
    if (!exhaustAnimation[2].loadFromFile("assets/flame3.png"))
        std::cerr << "Failed to load assets/flame3.png\n";
    if (!exhaustAnimation[3].loadFromFile("assets/flame4.png"))
        std::cerr << "Failed to load assets/flame4.png\n";

    exhaustVisual.setOrigin({ visual.getLocalBounds().size.x / 2, -visual.getLocalBounds().size.y / 2 });
    exhaustVisual.setPosition({ 800.f,450.f });// set origin 48 units above your ships origing because thats the height of ship

}

///// Code for making rotation affected by physics and acceleration //////
/*
void PlayerShip::rotateRight(float dt) {
    if (rotationVelocity.asDegrees() > -maxRotationVelocity.asDegrees())
        rotationVelocity -= rotationRate * dt;
}

void PlayerShip::rotateLeft(float dt) {
    if (rotationVelocity.asDegrees() < maxRotationVelocity.asDegrees())
        rotationVelocity += rotationRate * dt;
}
*/



// based of input from w key the thrust is added to the velocity of the ship
void PlayerShip::forwardPropulsion(float dt)
{
    // increasing the velocity in whatever dirction based on w key being pressed.
    float xDirection = std::cos((hitBox.getRotation().asDegrees() - 90) * 3.14159265f / 180.f);
    float yDirection = std::sin((hitBox.getRotation().asDegrees() - 90) * 3.14159265f / 180.f);
    acceleration = { speed * dt * xDirection, speed * dt * yDirection };
    velocity = (velocity + acceleration);

    thrustActived = true;
    exhaustDuration += dt;
}

// input is the the other object its colliding with mass and velocity
//CURENTTLY NOTE USING MIGHT GET RID OF
void PlayerShip::collision(float otherMass, sf::Vector2f otherVelocity)
{
    /*
    // new velocity direciton
        velocity = velocity * -1.f;

    // moves the ship 1 in x and y direction that your new oppositive velocity is so that it doesn't get stuck
    // although I don't think this will really work when the ship doesn't necesarrily full change direction right
    // So i think I should do more of a check to see if hit boxes are still colliding after velocity change with like
    // a > check and then set positoin after that
    // I think im going to need to assing mass to objects so that I based on there mass/weight they are affected more or less by
    // objects the hit. IE intertia
    // could even add fiction constant to help kind of introduced likea drag type thing that slows down total velcoity of all things
    sf::Vector2f newpos = hitBox.getPosition() + sf::Vector2f(
        velocity.x / abs(velocity.x), //velocity.x / abs(velocity.x) gets the purely the direction that object is now in.
        velocity.y / abs(velocity.y)
    );
    
    
    */
    velocity.x = ((mass - otherMass) / (mass + otherMass)) * velocity.x
        + ((2 * otherMass) / (mass + otherMass)) * otherVelocity.x;
    velocity.y = ((mass - otherMass) / (mass + otherMass)) * velocity.y
        + ((2 * otherMass) / (mass + otherMass)) * otherVelocity.y;

    /*
    

    // Step 2: set positions
    hitBox.setPosition(newpos);
    visual.setPosition(newpos);
    exhaustVisual.setPosition(newpos);

    
    */
}

// simply updates Everything about the ship to get ready for rendering
void PlayerShip::update(float dt)
{
    // updating position of ship
    hitBox.move(velocity * dt);
    visual.move(velocity * dt);
    exhaustVisual.move(velocity * dt);

    // Logic for smooth animation of rocket Exahust.
    if (exhaustDuration > 0)
    {
        if (exhaustDuration < 0.07f)
            exhaustVisual.setTexture(exhaustAnimation[0]);
        else if (exhaustDuration < 0.15f)
            exhaustVisual.setTexture(exhaustAnimation[1]);
        else if (exhaustDuration < 0.25f)
            exhaustVisual.setTexture(exhaustAnimation[2]);
        else
        {
            exhaustVisual.setTexture(exhaustAnimation[3]);
            exhaustDuration = 0.24f; // cap it at max flame
        }
    }
    if (not thrustActived)
    {
        exhaustDuration -= dt;
        if (exhaustDuration < 0.f)
            exhaustDuration = 0.f;
    }
    thrustActived = false;
}

// draws the ship and its exhaust
void PlayerShip::draw(sf::RenderWindow& window)
{
    // by the way draw the hit box at some point to make sure it matches texture use transparency
    window.draw(visual);

    if (exhaustDuration > 0)
    {
        window.draw(exhaustVisual);
    }
}