#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <iostream>


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
    void respawn() {
        visual.setPosition(sf::Vector2f(500.f, 500.f)); // can randomize later
        hitBox.setPosition(sf::Vector2f(500.f, 500.f));
        velocity = { sf::Vector2f(0.f, 0.f) };
        health = 100;
    }

    sf::ConvexShape getHitBox() { return hitBox; } // maybe need
    sf::FloatRect getGlobalPos() { return hitBox.getGlobalBounds(); }
    sf::Vector2f getVelocity() { return velocity; }
    float getMass() { return mass; }

    int getHealth() { return health; }
    int getDamage() { return damage; }

    void setVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; }
    void setHealth(int newHealth) { health = newHealth; }

private:
    // maybe add struct for textures later
    sf::Sprite visual; // 


    sf::ConvexShape hitBox; // use this for collsions and phyrics and what not
    int health{ 150 };
    int damage{ 100 }; 


    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass{ 4000.f };

};

