
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
    // Initiating objects
    auto window = sf::RenderWindow(sf::VideoMode({ 1600u, 900u }), "Spcae dodger");
    window.setFramerateLimit(240);

    TEXTURES.load();

    bool paused{ false };

    PlayerShip player;

    std::vector<Meteor> meteors;
    meteors.reserve(42);
    for (int i = 0; i < 30; ++i) meteors.emplace_back(); // small
    for (int i = 0; i < 10; ++i) meteors.emplace_back(2); // medium
    for (int i = 0; i < 2; ++i)  meteors.emplace_back(4); // large

    Physics physics;

    sf::Clock clock;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    while (window.isOpen())
    {
        // time mechanics
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) // window interation
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            } 
            if (event->is<sf::Event::KeyPressed>() and
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
            {
                paused = !paused;          
            }
        }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // pausing/ending game  
        if (player.getHealth() <= 0) // close window if player has no health
        {
            window.close();
            break;
        }

        if (paused)
        {
            window.clear(sf::Color(0, 0, 0));
            player.draw(window);
            window.display();
            continue;
        }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // inputs

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { player.forwardPropulsion(dt); }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { player.rotateRight(dt); }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { player.rotateLeft(dt); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // updates

        player.update(dt);

        for (std::size_t i{ 0 }; i < meteors.size(); ++i) // meteors
        {
            meteors[i].update(dt);
        }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // collisions

        //player vs meteors
        for (int i{ 0 }; i < meteors.size(); ++i)
        {
            if (player.getGlobalPos().findIntersection(meteors[i].getGlobalPos()))
            {
                physics.collision(player, meteors[i]);
            }
        }

        // meteors vs meteors
        for (std::size_t i{ 0 }; i < meteors.size(); ++i)
        {
            for (std::size_t k{ i + 1 }; k < meteors.size(); ++k)
            {
                if (meteors[i].getGlobalPos().findIntersection(meteors[k].getGlobalPos()))
                {
                    physics.collision(meteors[i], meteors[k]);
                }
            }
        }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // render
        window.clear(sf::Color(25, 25, 112));
        player.draw(window);

        for (std::size_t i{0}; i < meteors.size(); ++i) // meteors
        {
            meteors[i].draw(window);
        }

        window.display();


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fps counter to console
        static int frames = 0;
        static sf::Clock fpsClock;

        frames++;

        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f)
        {
            std::cout << "FPS: " << frames << "\n";
            frames = 0;
            fpsClock.restart();
        }

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
