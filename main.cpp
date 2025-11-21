

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

    sf::Sprite background(TEXTURES.backgroundtexture);
    background.scale({ 1.1,1.1 });

    bool paused{ false };

    PlayerShip player;

    std::vector<Meteor> meteors;
    meteors.reserve(80);
    for (int i = 0; i < 50; ++i) meteors.emplace_back(); // small
    for (int i = 0; i < 20; ++i) meteors.emplace_back(2); // medium
    for (int i = 0; i < 10; ++i)  meteors.emplace_back(4); // large

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

        window.draw(background);
        player.draw(window);
        for (std::size_t i{ 0 }; i < meteors.size(); ++i) // meteors
        {
            meteors[i].draw(window);
        }

        window.display();

    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

