
//#include <SFML/OpenGL.hpp>

#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerShip.h"
#include "Meteor.h"
#include "Physics.h"
#include "Textures.h"
#include <vector>


int main()
{

    auto window = sf::RenderWindow(sf::VideoMode({ 1600u, 900u }), "Spcae dodger");
    window.setFramerateLimit(240);

    TEXTURES.load();


    bool paused{ false };


    PlayerShip player;

    Meteor meteor;

    //std::array<Meteor, 30> Meteors;
    //for (int i{0}; i < 30; ++i)
    //{
        // Meteor meteor;
        //Meteors[i] = Meteor();
    //}


    Physics physics;

    sf::Clock clock;


    while (window.isOpen())
    {

        // time mechanics
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
                
            if (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
            {
                paused = !paused;
                // Do something once when Escape is pressed
                // For example: pause the game or open a menu
                    
            }

        }
        // close window if player has no health
        if (player.getHealth() <= 0)
        {
            window.close();
            break;
        }

        if (paused)
        {
            window.clear(sf::Color(0, 0, 0));
            player.draw(window);
            meteor.draw(window);
            window.display();
            continue;
        }

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
        meteor.update(dt);


        // collisions
        if (player.getGlobalPos().findIntersection(meteor.getGlobalPos()))
        {
            physics.collision(player, meteor);

            //meteor.collision(player.getMass(), player.getVelocity());
            //player.collision(meteor.getMass(), meteor.getVelocity());
        }


        // render
        window.clear(sf::Color(25, 25, 112));
        player.draw(window);
        meteor.draw(window);
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
