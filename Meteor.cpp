#include "Meteor.h"

Meteor::Meteor()
    : texture("assets/player.png"), visual(texture)
{
    if (!texture.loadFromFile("assets/flame1.png"))
        std::cerr << "Failed to load assets/flame1.png\n";
    visual.setPosition({ 801.f,450.f });
}


void Meteor::update(float dt)
{
    hitBox.move(velocity * dt);
    visual.move(velocity * dt);
    visual.setTexture(texture);
}


void Meteor::draw(sf::RenderWindow& window)
{

    window.draw(visual);
}