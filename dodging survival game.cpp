// dodging survival game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

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
        ship.setPosition(location);
    }

    void moveUp() { ship.move({ 0.f, -1.f }); }
    void moveLeft() { ship.move({ -1.f, 0.f }); }
    void moveDown() { ship.move({ 0.f, 1.f }); }
    void moveRight() { ship.move({ 1.f, 0.f }); }

    void update(float moving)
    {

        // well I know I want the ship to continue moving desppite no key being pressed
    }


    sf::Vector2f getLocation()
    {
        // maybe need idk
        return location;
    }


    
    void draw(sf::RenderWindow& window)
    {
        window.draw(ship);
    }


    private:
        sf::ConvexShape ship;
        sf::Vector2f location{800.f,450.f};
        int health { 100 };

		float speedMultiplier{ 300.f };

};




int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1600u, 900u }), "Spcae dodger");
    window.setFramerateLimit(144);

    PlayerShip player{};


    while (window.isOpen())
    {
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }


        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){player.moveUp();}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){player.moveLeft();}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){player.moveDown();}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){player.moveRight();}



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
