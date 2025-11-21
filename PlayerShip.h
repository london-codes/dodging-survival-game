#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <iostream>

// Make Base class for inheritance so health damage velocity can be part of any object quickly
class PlayerShip
{
public:
    PlayerShip();

    void rotateRight(float dt) {
        visual.rotate(-rotationRate * dt);
        hitBox.rotate(-rotationRate * dt);
        exhaustVisual.rotate(-rotationRate * dt);
    }

    void rotateLeft(float dt) {
        visual.rotate(rotationRate * dt);
        hitBox.rotate(rotationRate * dt);
        exhaustVisual.rotate(rotationRate * dt);
    }

    // w key to move forward increasing velocity in the direction ship is pointed
    void forwardPropulsion(float dt);

    // updates everything about the ship to get ready for rendering
    void update(float dt);

    // draws the ship and its exhaust
    void draw(sf::RenderWindow& window);

    void takeDamage(int amount) {
        currHealth -= amount;
    }

    sf::ConvexShape getHitBox() { return hitBox; }
    sf::FloatRect getGlobalPos() { return hitBox.getGlobalBounds(); }
    sf::Vector2f getVelocity() { return velocity; }
    float getMass() { return mass; }

    int getHealth() { return currHealth; }
    int getDamage() { return damage; }
    bool getInPlay() { return inPlay; }

    void moveAll(sf::Vector2f amountMove){
        hitBox.move(amountMove);
        visual.move(amountMove);
        healthBar.move(amountMove);
        exhaustVisual.move(amountMove);
    }
    void setAllPositions(float x, float y) { // sets all sprites and hitboxes to necssary positions
        hitBox.setPosition({ x, y });
        visual.setPosition({ x, y });
        exhaustVisual.setPosition({ x, y });
        healthBar.setPosition({ visual.getPosition().x - 26.f, visual.getPosition().y + 30.f }); // different since its origin is not set correctly
    }
    void setVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; }
    void setHealth(int newHealth) { currHealth = newHealth; };
private:

    // visuals
    sf::Sprite visual;
    sf::Sprite exhaustVisual; // for visual animation of thruster
    bool thrustActived = false;
    float exhaustDuration{ 0 };
    sf::RectangleShape healthBar{ { 50.f, 10.f } };

    // collisions / physics
    sf::ConvexShape hitBox;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass{ 1801 };
    float speed{ 300.f };
    int maxHealth{ 1000 };
    int currHealth{ 1000 };
    int damage{ 50 };
    bool inPlay{ true };


    sf::Angle rotationRate{ sf::degrees(270.f) };

    //// phyiscs style rotation ////
    /*
     sf::Angle maxRotationVelocity{ sf::degrees(270.f) };
    sf::Angle rotationVelocity; // testing a more velocity and acceleration based rotation rather than just instant fixed
    */

};