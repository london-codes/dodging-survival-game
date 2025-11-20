#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <iostream>
#include "Random.h"
#include <utility>

class Meteor
{

public:

    Meteor();

    // some type of random type fucntion taht gets a random velcoity and position to set the vlecotiy of it do

    void collision(float, sf::Vector2f);

    void update(float dt);

    void draw(sf::RenderWindow& window);

    void takeDamage(int amount) {
        health -= amount;
        if (health <= 0) respawn();
    }
    ///////////////////////////////////////////////////////// fix when random is enabled so set of random screen position

        // gist of what its gonna do is really set up the metor to be launched so
        // based on given speed calcs its velcoity which its direction will be based on its position off screen 
        // so that it is show out in a direction so that will appear on the main screen.
        // ////////////
        // sets future velcoity for when shot out, its random postion off screen, the direciton it should shoot so it
        // appears on screen, the time it will shout out in the next 30 seconds

    sf::ConvexShape getHitBox() { return hitBox; } // maybe need
    sf::FloatRect getGlobalPos() { return hitBox.getGlobalBounds(); }
    sf::Vector2f getVelocity() { return velocity; }
    float getMass() { return mass; }

    int getHealth() { return health; }
    int getDamage() { return damage; }

    void setVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; }
    void setHealth(int newHealth) { health = newHealth; }

private:

    void respawn();

private:

    sf::Sprite visual; 

    // collisions
    sf::ConvexShape hitBox; 
    int health{ 150 };
    int damage{ 100 }; 

    // launch timing 
    static inline sf::Clock launchClock; // shared clock
    sf::Vector2f launchVelocity{ 300, 0 }; // set for etsing for now
    float launchTime;

    // current physics
    float maxSpeed{ 400.f }; // for now
    float minSpeed{ 20.f };
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass{ 4000.f };

};

