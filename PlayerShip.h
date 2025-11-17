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


    void rotateRight(float dt) { visual.rotate(-rotationRate * dt);
        hitBox.rotate(-rotationRate * dt);
        exhaustVisual.rotate(-rotationRate * dt); }
    
    void rotateLeft(float dt) {
        visual.rotate(rotationRate * dt);
        hitBox.rotate(rotationRate * dt);
        exhaustVisual.rotate(rotationRate * dt);
    }


    // based of input from w key the thrust is added to the velocity of the ship
    void forwardPropulsion(float dt);

    void collision(float, sf::Vector2f);

    // simply updates Everything about the ship to get ready for rendering
    void update(float dt);

    // draws the ship and its exhaust
    void draw(sf::RenderWindow& window);

    void takeDamage(int amount) {
        health -= amount;
        if (health <= 0) gameOver();
    }

    void gameOver() {
        //end game here somehow
    }

    sf::ConvexShape getHitBox() { return hitBox; }
    sf::FloatRect getGlobalPos() { return hitBox.getGlobalBounds(); }
    sf::Vector2f getVelocity() { return velocity; }
    float getMass() { return mass; }

    int getHealth() { return health; }
    int getDamage() { return damage; }

    void setVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; }
    void setHealth(int newHealth) { health = newHealth; };
private:

    sf::Sprite visual; // use for visual and animating stuff. Also use for shadows potentially


    sf::Sprite exhaustVisual; // for visual animation of thruster
    bool thrustActived = false;
    float exhaustDuration{ 0 };

    sf::ConvexShape hitBox; // use this for collsions and phyrics and what not
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass{ 1001 };
    float speed{ 300.f };
    int health{ 1000 };
    int damage{ 50 };


    sf::Angle rotationRate{ sf::degrees(270.f) };

    //// phyiscs style rotation ////
    /*
     sf::Angle maxRotationVelocity{ sf::degrees(270.f) };
    sf::Angle rotationVelocity; // testing a more velocity and acceleration based rotation rather than just instant fixed
    */

};