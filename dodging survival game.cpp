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
        ship.setPosition(sf::Vector2f {800, 450});
    }

    sf::ConvexShape& getShipDraw()
    {
        return ship;
    }
   

    private:
        sf::ConvexShape ship;
        int health { 100 };

};




int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1600u, 900u }), "Spcae dodger");
    window.setFramerateLimit(144);

    PlayerShip playerShip{};


    while (window.isOpen())
    {
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }


        }

        window.clear();


        window.draw(playerShip.getShipDraw());

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
