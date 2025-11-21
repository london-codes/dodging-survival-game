#include "PlayerShip.h"
#include "Textures.h"

PlayerShip::PlayerShip()
    : visual(TEXTURES.playerShip), exhaustVisual(TEXTURES.playerShip) // sf::Sprite has no default constructor so it needs to be initializer list with dummy texture
{
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

    // exhaust visuals
    exhaustVisual.setOrigin({ visual.getLocalBounds().size.x / 2, -visual.getLocalBounds().size.y / 2 });
    exhaustVisual.setPosition({ 800.f,450.f });// set origin 48 units above your ships origing because thats the height of ship

}

// based of input from w key the thrust is added to the velocity of the ship
void PlayerShip::forwardPropulsion(float dt)
{
    constexpr float DEG_TO_RAD = 3.14159265f / 180.f;
    // increasing the velocity in whatever dirction based on w key being pressed.
    float xDirection = std::cos((hitBox.getRotation().asDegrees() - 90) * DEG_TO_RAD);
    float yDirection = std::sin((hitBox.getRotation().asDegrees() - 90) * DEG_TO_RAD);
    acceleration = { speed * dt * xDirection, speed * dt * yDirection };
    velocity = (velocity + acceleration);

    thrustActived = true;
    exhaustDuration += dt;
}

// updates everything about the ship to get ready for rendering
void PlayerShip::update(float dt)
{
    // updating position of ship
    hitBox.move(velocity * dt);
    visual.move(velocity * dt);
    exhaustVisual.move(velocity * dt);

    // Keep ship within the bounds of 1600x900 screen
    sf::Vector2f pos = visual.getPosition();
    if (pos.x < 0){
        hitBox.setPosition({ 0.f, pos.y });
        visual.setPosition({ 0.f, pos.y });
        exhaustVisual.setPosition({ 0.f, pos.y });
        velocity = { 0, velocity.y };
    }
    if (pos.x > 1600){
        hitBox.setPosition({ 1600.f, pos.y });
        visual.setPosition({ 1600.f, pos.y });
        exhaustVisual.setPosition({ 1600.f, pos.y });
        velocity = { 0, velocity.y };

    }
    if (pos.y > 900) {
        hitBox.setPosition({ pos.x, 900.f });
        visual.setPosition({ pos.x, 900.f });
        exhaustVisual.setPosition({ pos.x, 900.f });
        velocity = { velocity.x, 0 };
    }
    if (pos.y < 0) {
        hitBox.setPosition({ pos.x, 0.f });
        visual.setPosition({ pos.x, 0.f });
        exhaustVisual.setPosition({ pos.x, 0.f });
        velocity = { velocity.x, 0 };
    }

    // rocekt exhaust animation.
    if (exhaustDuration > 0)
    {
        if (exhaustDuration < 0.07f) // time the first animation lasts etc
            exhaustVisual.setTexture(TEXTURES.exhaustAnimation[0]);
        else if (exhaustDuration < 0.15f)
            exhaustVisual.setTexture(TEXTURES.exhaustAnimation[1]);
        else if (exhaustDuration < 0.25f)
            exhaustVisual.setTexture(TEXTURES.exhaustAnimation[2]);
        else
        {
            exhaustVisual.setTexture(TEXTURES.exhaustAnimation[3]);
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

void PlayerShip::draw(sf::RenderWindow& window)
{
    window.draw(visual);

    if (exhaustDuration > 0)
    {
        window.draw(exhaustVisual);
    }
}

///// Code for making rotation affected by physics and acceleration //////// didn't like this it made it to slow.
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