// dodging survival game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <cmath>


class PlayerShip
{
public:
    PlayerShip()
    {
        ship.setPointCount(4);
        ship.setPoint(0, { -15.f, -30.f });
        ship.setPoint(1, { 15.f, -30.f });
        ship.setPoint(2, { 25.f, 30.f });
        ship.setPoint(3, { -25.f, 30.f });
        ship.setPosition({ 800.f,450.f });
        ship.setRotation(sf::degrees(0));
    }
    // moves the ship faster and faster based on the timing of the w key but also when no being pressed has its own timer that starts to declerate the speed
    // towards zero

    void rotateRight() { ship.rotate(sf::degrees(-2)); }
    void rotateLeft() { ship.rotate(sf::degrees(2)); }

    // calc accelreation which really is just a velocity and add it to the current velocity

    // this funciton will beused to change the momentum / vleocity of the ship
    void forwardThrust(float time)
    {
        float xDirection = std::cos((ship.getRotation().asDegrees() - 90) * 3.14159265f / 180.f);
        float yDirection = std::sin((ship.getRotation().asDegrees() - 90) * 3.14159265f / 180.f);
        acceleration = { speed * time * xDirection, speed * time * yDirection };
        velocity = velocity + acceleration;
        acceleration = { 0, 0 };
    }

    // simply updates the position of the ship every frame based on the ships current velocity which is stored in private
    void update()
    {
        ship.move(velocity);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(ship);
    }

private:
    sf::ConvexShape ship; // general ship infomraiton like shape, orietnation, rotation, also includes move commands 
    sf::Vector2f velocity; // used to simply apply update to so that there is mommentum and stuff keeps moving if your not thrustinmg your dick in my butt
    sf::Vector2f acceleration;
    int health{ 100 };
    float speed{ 3.f };

};

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1600u, 900u }), "Spcae dodger");
    window.setFramerateLimit(144);

    PlayerShip player{};

    sf::Clock clock;

    int frame = 0;
    float total = 0;

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
        window.clear();
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
