#include "Meteor.h"

Meteor::Meteor()
    : texture("assets/meteor.png"), visual(texture)
{
    // hit box
    hitBox.setPointCount(4);
    hitBox.setPoint(0, sf::Vector2f{ -7, -8 });
    hitBox.setPoint(1, sf::Vector2f{ 8, -8 });
    hitBox.setPoint(2, sf::Vector2f{ 8, 7 });
    hitBox.setPoint(3, sf::Vector2f{ -7, 7 });
    hitBox.setPosition({ 850.f,450.f });

    // visual
    visual.setOrigin({ visual.getLocalBounds().size.x / 2, visual.getLocalBounds().size.y / 2 });
    visual.setPosition({ 850.f,450.f });
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