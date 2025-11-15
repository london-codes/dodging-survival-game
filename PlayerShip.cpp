#include "PlayerShip.h"


PlayerShip::PlayerShip()
    : shipTexture("assets/playership.png"), shipVisual(shipTexture),
    exhaustVisual(shipTexture) // sf::Sprite has not default constructor so it needs to be initializer list with dummy texture
{
    // For Both the HitBox and Visual I think the origin of rotaiton might need to be adjusted so that it matches how it moves better.
    // HitBox
    shipHitBox.setPointCount(8);
    // roughly hitbox for now I'll adjust when I have something to test collsiosn with // could use all positive values and just corretly set orgin after
    shipHitBox.setPoint(0, sf::Vector2f{ -7, -20 });
    shipHitBox.setPoint(1, sf::Vector2f{ 7, -20 });
    shipHitBox.setPoint(2, sf::Vector2f{ 7, 10 });
    shipHitBox.setPoint(3, sf::Vector2f{ 15, 10 });
    shipHitBox.setPoint(4, sf::Vector2f{ 15, 22 });
    shipHitBox.setPoint(5, sf::Vector2f{ -15, 22 });
    shipHitBox.setPoint(6, sf::Vector2f{ -15, 10 });
    shipHitBox.setPoint(7, sf::Vector2f{ -7, 10 });
    shipHitBox.setPosition({ 800.f,450.f });

    //Ship visuals
    shipVisual.setScale({ 1.f, 1.f });
    shipVisual.setOrigin({ shipVisual.getLocalBounds().size.x / 2, shipVisual.getLocalBounds().size.y / 2 });
    shipVisual.setPosition({ 800.f,450.f });

    // Thruster Visual
    if (!exhaustAnimation[0].loadFromFile("assets/flame1.png"))
        std::cerr << "Failed to load assets/flame1.png\n";
    if (!exhaustAnimation[1].loadFromFile("assets/flame2.png"))
        std::cerr << "Failed to load assets/flame2.png\n";
    if (!exhaustAnimation[2].loadFromFile("assets/flame3.png"))
        std::cerr << "Failed to load assets/flame3.png\n";
    if (!exhaustAnimation[3].loadFromFile("assets/flame4.png"))
        std::cerr << "Failed to load assets/flame4.png\n";

    exhaustVisual.setOrigin({ shipVisual.getLocalBounds().size.x / 2, -shipVisual.getLocalBounds().size.y / 2 });
    exhaustVisual.setPosition({ 800.f,450.f });// set origin 48 units above your ships origing because thats the height of ship

}

// based of input from w key the thrust is added to the velocity of the ship
void PlayerShip::forwardPropulsion(float dt)
{
    // increasing the velocity in whatever dirction based on w key being pressed.
    float xDirection = std::cos((shipHitBox.getRotation().asDegrees() - 90) * 3.14159265f / 180.f);
    float yDirection = std::sin((shipHitBox.getRotation().asDegrees() - 90) * 3.14159265f / 180.f);
    acceleration = { speed * dt * xDirection, speed * dt * yDirection };
    velocity = (velocity + acceleration);

    thrustActived = true;
    exhaustDuration += dt;
}

// simply updates Everything about the ship to get ready for rendering
void PlayerShip::update(float dt)
{
    // Moving all parts of the ship correctly.
    shipHitBox.move(velocity * dt);
    shipVisual.move(velocity * dt);
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
    window.draw(shipHitBox);
    window.draw(shipVisual);

    if (exhaustDuration > 0)
    {
        window.draw(exhaustVisual);
    }
}