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
        : shipTexture("assets/playership.png"), shipVisual(shipTexture), 
        exhaustTexture("assets/flame2.png"), exhaustVisual(exhaustTexture) // right now I need this intiated with dummy so that origin and position can be set
        // correctly. Maybe find a way so I don't have to intiate this with just one of the flame.png's
    {
        // For Both the HitBox and Visual I think the origin of rotaiton might need to be adjusted so that it matches how it moves better.

        // HitBox
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

        //Ship visuals
        shipVisual.setScale({1.f, 1.f});
        shipVisual.setOrigin({ shipVisual.getLocalBounds().size.x / 2, shipVisual.getLocalBounds().size.y / 2 });
        shipVisual.setPosition({ 800.f,450.f });

        // Thruster Visual
        exahustAnimation[0].loadFromFile("assets/flame1.png");
        exahustAnimation[1].loadFromFile("assets/flame2.png");
        exahustAnimation[2].loadFromFile("assets/flame3.png");
        exahustAnimation[3].loadFromFile("assets/flame4.png");
        exhaustVisual.setOrigin({ shipVisual.getLocalBounds().size.x / 2, -shipVisual.getLocalBounds().size.y / 2 });
        exhaustVisual.setPosition({ 800.f,450.f });// set origin 48 units above your ships origing because thats the height of ship
  
    }

    void rotateRight(float dt) { shipVisual.rotate(-rotationRate * dt); shipHitBox.rotate(-rotationRate * dt); exhaustVisual.rotate(-rotationRate * dt);  }
    void rotateLeft(float dt) { shipVisual.rotate(rotationRate * dt); shipHitBox.rotate(rotationRate * dt); exhaustVisual.rotate(rotationRate * dt);    }


    // based of input from w key the thrust is added to the velocity of the ship
    void forwardPropulsion(float dt)
    {
        // increasing the velocity in whatever dirction based on w key being pressed.
        float xDirection = std::cos((shipHitBox.getRotation().asDegrees() - 90) * 3.14159265f / 180.f);
        float yDirection = std::sin((shipHitBox.getRotation().asDegrees() - 90) * 3.14159265f / 180.f);
        acceleration = { speed * dt * xDirection, speed * dt * yDirection };
        velocity = (velocity + acceleration);

        thrustActived = true;
        exhaustDuration += dt;
    }

    // simply updates Everything about the ship to get ready for rendering
    void update(float dt)
    {
        // Moving all parts of the ship correctly.
        shipHitBox.move(velocity * dt);
        shipVisual.move(velocity * dt);
        exhaustVisual.move(velocity * dt);

        // Logic for smooth animation of rocket Exahust.
        if (exhaustDuration > 0)
        {
            if (exhaustDuration < 0.07f)
                exhaustVisual.setTexture(exahustAnimation[0]);
            else if (exhaustDuration < 0.15f)
                exhaustVisual.setTexture(exahustAnimation[1]);
            else if (exhaustDuration < 0.25f)
                exhaustVisual.setTexture(exahustAnimation[2]);
            else
            {
                exhaustVisual.setTexture(exahustAnimation[3]);
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

    // draws the ship and its exhaust
    void draw(sf::RenderWindow& window)
    {
        // by the way draw the hit box at some point to make sure it matches texture use transparency
        window.draw(shipVisual);

        if (exhaustDuration > 0)
        {
            window.draw(exhaustVisual);
        }
    }

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

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1600u, 900u }), "Spcae dodger");
    window.setFramerateLimit(240);

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
            player.forwardPropulsion(dt);
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            player.rotateRight(dt);
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.rotateLeft(dt);
        }

        // updates
        player.update(dt);

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
