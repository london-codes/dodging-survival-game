#include "Meteor.h"

Meteor::Meteor()
    : texture("assets/meteor.png"), visual(texture), velocity{ 100.f, 0.f } // to test
{


    // hit box
    hitBox.setPointCount(4);
    hitBox.setPoint(0, sf::Vector2f{ -7, -8 });
    hitBox.setPoint(1, sf::Vector2f{ 8, -8 });
    hitBox.setPoint(2, sf::Vector2f{ 8, 7 });
    hitBox.setPoint(3, sf::Vector2f{ -7, 7 });
    hitBox.setPosition({ 0.f,450.f });

    // visual
    visual.setOrigin({ visual.getLocalBounds().size.x / 2, visual.getLocalBounds().size.y / 2 });
    visual.setPosition({ 0.f,450.f });
}

//CURENTTLY NOTE USING MIGHT GET RID OF
void Meteor::collision(float otherMass, sf::Vector2f otherVelocity)
{
    //velocity = velocity * -1.f;

    velocity.x = ((mass - otherMass) / (mass + otherMass)) * velocity.x
        + ((2 * otherMass) / (mass + otherMass)) * otherVelocity.x;
    velocity.y = ((mass - otherMass) / (mass + otherMass)) * velocity.y
        + ((2 * otherMass) / (mass + otherMass)) * otherVelocity.y;

}

void Meteor::update(float dt)
{
    hitBox.move(velocity * dt);
    visual.move(velocity * dt);

}


void Meteor::draw(sf::RenderWindow& window)
{
    window.draw(visual);
}