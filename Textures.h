#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct Textures
{
public:
	sf::Texture meteor;
    sf::Texture playerShip; // 48 by 48 pixels
    std::array<sf::Texture, 4> exhaustAnimation;

void load() {
    if (!meteor.loadFromFile("assets/meteor.png"))
        std::cout << "Failed to load meteor!\n";

    if (!playerShip.loadFromFile("assets/playership.png"))
        std::cout << "Failed to load playership!\n";
    // exhaust visuals
    if (!exhaustAnimation[0].loadFromFile("assets/flame1.png"))
        std::cerr << "Failed to load assets/flame1.png\n";
    if (!exhaustAnimation[1].loadFromFile("assets/flame2.png"))
        std::cerr << "Failed to load assets/flame2.png\n";
    if (!exhaustAnimation[2].loadFromFile("assets/flame3.png"))
        std::cerr << "Failed to load assets/flame3.png\n";
    if (!exhaustAnimation[3].loadFromFile("assets/flame4.png"))
        std::cerr << "Failed to load assets/flame4.png\n";

}
};

inline Textures TEXTURES;