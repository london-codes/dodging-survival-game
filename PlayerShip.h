#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class PlayerShip
{
public:
    PlayerShip();

    void rotateRight(float dt) { shipVisual.rotate(-rotationRate * dt); shipHitBox.rotate(-rotationRate * dt); exhaustVisual.rotate(-rotationRate * dt); }
    void rotateLeft(float dt) { shipVisual.rotate(rotationRate * dt); shipHitBox.rotate(rotationRate * dt); exhaustVisual.rotate(rotationRate * dt); }

    // based of input from w key the thrust is added to the velocity of the ship
    void forwardPropulsion(float dt);

    // simply updates Everything about the ship to get ready for rendering
    void update(float dt);

    // draws the ship and its exhaust
    void draw(sf::RenderWindow& window);

private:
    sf::Texture shipTexture; // 48 by 48 pixels
    sf::Sprite shipVisual; // use for visual and animating stuff. Also use for shadows potentially

    std::array<sf::Texture, 4> exahustAnimation;
    sf::Texture exhaustTexture;
    sf::Sprite exhaustVisual; // for visual animation of thruster
    bool thrustActived = false;
    float exhaustDuration{ 0 };

    sf::ConvexShape shipHitBox; // use this for collsions and phyrics and what not
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Angle rotationRate{ sf::degrees(270.f) };
    int health{ 100 };
    float speed{ 300.f };
};