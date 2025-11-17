#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <iostream>

class Physics
{
public:
	Physics();


    // templates need to go in header file for a class unless other wise intiated explictly
    template <typename T, typename V>
    void collision(T& object1, V& object2)
    {
        // intial velocites
        sf::Vector2f v1 = object1.getVelocity();
        sf::Vector2f v2 = object2.getVelocity();

        // masses
        float m1 = object1.getMass();
        float m2 = object2.getMass();

        // calculating new velocities
        sf::Vector2f newV1;
        sf::Vector2f newV2;

        newV1.x = ((m1 - m2) / (m1 + m2)) * v1.x + ((2 * m2) / (m1 + m2)) * v2.x;
        newV1.y = ((m1 - m2) / (m1 + m2)) * v1.y + ((2 * m2) / (m1 + m2)) * v2.y;

        newV2.x = ((2 * m1) / (m1 + m2)) * v1.x + ((m2 - m1) / (m1 + m2)) * v2.x;
        newV2.y = ((2 * m1) / (m1 + m2)) * v1.y + ((m2 - m1) / (m1 + m2)) * v2.y;

        object1.setVelocity(newV1);
        object2.setVelocity(newV2);

        // calculate new healths
        object1.takeDamage(object2.getDamage());
        object2.takeDamage(object1.getDamage());
    }

private:
	float gravity;
};

