// dodging survival game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <cmath>

// Make into HEADER at some point
//constant pi

// seperate file for it as some point
class PlayerShip
{
public:
    PlayerShip()
        : texture("assets/player.png"), shipVisual(texture)
    {
        shipHitBox.setPointCount(8);
        // roughly hitbox for now I'll adjust when I have something to test collsiosn with // could use all positive values and just corretly set orgin after
        shipHitBox.setPoint(0, sf::Vector2f{-10, -20 });
        shipHitBox.setPoint(1, sf::Vector2f{10, -20 });
        shipHitBox.setPoint(2, sf::Vector2f{10, 10 });
        shipHitBox.setPoint(3, sf::Vector2f{15, 10 });
        shipHitBox.setPoint(4, sf::Vector2f{15, 20 });
        shipHitBox.setPoint(5, sf::Vector2f{-15, 20 });
        shipHitBox.setPoint(6, sf::Vector2f{-15, 10 });
        shipHitBox.setPoint(7, sf::Vector2f{-10, 10 });
        shipHitBox.setPosition({ 800.f,450.f });

        // need to fix origin of sprite so rotation looks normal
        shipVisual.setScale(sf::Vector2f {2.f, 2.f});
        shipVisual.setPosition({ 800.f,450.f });
    }

    void rotateRight() { shipVisual.rotate(-rotationRate); shipHitBox.rotate(-rotationRate); }
    void rotateLeft() { shipVisual.rotate(rotationRate); shipHitBox.rotate(rotationRate); }


    // based of input from w key the thrust is added to the velocity of the ship
    void forwardThrust(float time)
    {
        float xDirection = std::cos((shipHitBox.getRotation().asDegrees() - 90) * 3.14159265f / 180.f);
        float yDirection = std::sin((shipHitBox.getRotation().asDegrees() - 90) * 3.14159265f / 180.f);
        acceleration = { speed * time * xDirection, speed * time * yDirection };
        velocity = velocity + acceleration;
        acceleration = { 0, 0 };
    }

    // simply updates the position of the ship every frame based on the ships current velocity which is stored in private
    void update()
    {
        shipVisual.move(velocity);
        shipHitBox.move(velocity);
    }

    void draw(sf::RenderWindow& window)
    {
        // by the way draw the hit box at some point to make sure it matches texture use transparency
        window.draw(shipVisual);
    }

private:
    sf::Texture texture;
    sf::Sprite shipVisual; // use for visual and animating stuff. Also use for shadows potentially
    // At some point add second shipVisualRocket for thruster animation spereately
    sf::ConvexShape shipHitBox; // use this for collsions and phyrics and what not
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Angle rotationRate{ sf::degrees(1.5f) };
    int health{ 100 };
    float speed{ 2.f };
};

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1600u, 900u }), "Spcae dodger");
    window.setFramerateLimit(144);

    PlayerShip player;

    sf::Clock clock;


    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }


        }

        // time mechanics
        float dt = clock.restart().asSeconds();

        // inputs
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            player.forwardThrust(dt);
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            player.rotateRight();
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.rotateLeft();
        }

        // updates
        player.update();

        // render
        window.clear(sf::Color(25, 25, 112));
        player.draw(window);
        window.display();
    }
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
