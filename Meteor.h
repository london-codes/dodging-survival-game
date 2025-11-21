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

    Meteor(float size = 1);

    void update(float dt);

    void draw(sf::RenderWindow& window);

    void takeDamage(int amount) {
        currHealth -= amount;
        if (currHealth <= 0) respawn();
    }

    sf::ConvexShape getHitBox() { return hitBox; } // maybe need
    sf::FloatRect getGlobalPos() { return hitBox.getGlobalBounds(); }
    sf::Vector2f getVelocity() { return velocity; }
    float getMass() { return mass; }

    int getHealth() { return currHealth; }
    int getDamage() { return damage; }
    bool getInPlay() { return inPlay; }

    void moveAll(sf::Vector2f amountMove) {
        hitBox.move(amountMove);
        visual.move(amountMove);
    }
    void setAllPositions(float x, float y) { // sets all sprites and hitboxes to necssary positions
        hitBox.setPosition({ x, y });
        visual.setPosition({ x, y });
    }
    void setVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; }
    void setHealth(int newHealth) { currHealth = newHealth; }

private:

    void respawn();

private:

    sf::Sprite visual; 

    // collisions / physics
    sf::ConvexShape hitBox;
    bool inPlay{false};
    float size_m;
    int currHealth;
    int maxHealth{ 201 };
    int damage{ 100 }; 
    float maxSpeed{ 400.f }; // for now
    float minSpeed{ 20.f };
    sf::Vector2f velocity;
    float mass{ 1000.f };

    // launch timing 
    static inline sf::Clock launchClock; // shared clock
    sf::Vector2f launchVelocity;
    float launchTime;
};

