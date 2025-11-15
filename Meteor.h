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



    void update(float dt);

    void draw(sf::RenderWindow& window);

private:
    sf::Texture texture; // 
    sf::Sprite visual; // 


    sf::ConvexShape hitBox; // use this for collsions and phyrics and what not
    int health{ 100 };


    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float speed{ 300.f };
};

