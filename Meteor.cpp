#include "Meteor.h"
#include "Textures.h"


Meteor::Meteor()// size with default value and I think thats it
    : visual(TEXTURES.meteor)
{
    // hit box
    hitBox.setPointCount(4);
    hitBox.setPoint(0, sf::Vector2f{ -7, -8 });
    hitBox.setPoint(1, sf::Vector2f{ 8, -8 });
    hitBox.setPoint(2, sf::Vector2f{ 8, 7 });
    hitBox.setPoint(3, sf::Vector2f{ -7, 7 });
    hitBox.setPosition({ 100.f,450.f });

    // visual
    visual.setOrigin({ visual.getLocalBounds().size.x / 2, visual.getLocalBounds().size.y / 2 });
    visual.setPosition({ 100.f,450.f });

    // launch mechanics
    respawn();

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
    if (launchTime <= launchClock.getElapsedTime().asSeconds())
    {
        velocity = launchVelocity;
        launchTime = 100.f;
    }
        

    hitBox.move(velocity * dt);
    visual.move(velocity * dt);

}


void Meteor::draw(sf::RenderWindow& window)
{
    window.draw(visual);
}

/*


std::pair<sf::Vector2f, float> SpawnInfo(int screenWidth, int screenHeight)
{
    constexpr float RAD_TO_DEG = 180.f / 3.14159265f;
    int side = Random::get(0, 3); // 0=top, 1=right, 2=bottom, 3=left
    side = 3;
    sf::Vector2f pos;
    float angle;

    switch (side) {
    case 0: // top
        pos = { static_cast<float>(Random::get(0, screenWidth)), 0.f };
        angle = static_cast<float>(Random::get(20, 160)); // roughly pointing downward
        break;
    case 1: // right
        pos = { static_cast<float>(screenWidth), static_cast<float>(Random::get(0, screenHeight)) };
        // calcing angle to be shot
        // auto top = std::atan(screenWidth / pos.y);
        float bottom = -90.f + std::atan(static_cast<float>(screenWidth) / (900.f - pos.y));
        angle = bottom; // roughly pointing left

        break;
    case 2: // bottom
        pos = { static_cast<float>(Random::get(0, screenWidth)), static_cast<float>(screenHeight) };

        float topAngle = std::atan(pos.y / screenWidth) * RAD_TO_DEG;
        float bottomAngle = -std::atan((screenHeight - pos.y) / screenWidth) * RAD_TO_DEG; // this works
        float angle = static_cast<float>(Random::get(static_cast<int>(bottomAngle), static_cast<int>(topAngle)));

        break;
    case 3: // left

        pos = { 0.f, static_cast<float>(Random::get(0, screenHeight)) };
        std::cout << pos.y << std::endl;
        float topAngle = std::atan(pos.y / screenWidth) * RAD_TO_DEG;
        float bottomAngle = -std::atan((screenHeight - pos.y) / screenWidth) * RAD_TO_DEG; // this works
        float angle = static_cast<float>(Random::get(static_cast<int>(bottomAngle), static_cast<int>(topAngle)));
        std::cout << topAngle << std::endl;
        std::cout << bottomAngle << std::endl;
        break;
    default:
        pos = { 0.f, 0.f };
        angle = 0;
    }

    return { pos, angle };
}
*/
/*

    int side = Random::get(0, 3); // 0=top, 1=right, 2=bottom, 3=left
    sf::Vector2f pos;
    float angle;
    pos = { 0.f, (Random::get(0.f, screenHeight)) };

    std::cout << pos.y << std::endl;

    float topAngle = std::atan2((pos.y) , screenWidth);
    float bottomAngle = std::atan2(pos.y - screenHeight , screenWidth); // this works
    float test = (Random::get(bottomAngle, topAngle));
    std::cout << topAngle* 180 / 3.14159265<< std::endl;
    std::cout << bottomAngle* 180 / 3.14159265 << std::endl;

    angle = test; // roughly pointing left
*/

/*

// could switch to radians but degrees is more intuitive. Also easier to use with the randon number generator.
std::pair<sf::Vector2f, float> SpawnInfo(float screenWidth, float screenHeight)
{
    constexpr float RAD_TO_DEG = 180.f / 3.14159265f;

    int side = Random::get(0, 3); // 0=top, 1=right, 2=bottom, 3=left
    sf::Vector2f pos;
    float angle;
    pos = { 0.f, static_cast<float>(Random::get(0, screenHeight)) };

    std::cout << pos.y << std::endl;

    float topAngle = std::atan(pos.y / screenWidth) * RAD_TO_DEG;
    float bottomAngle = -std::atan((screenHeight - pos.y) / screenWidth) * RAD_TO_DEG; // this works
    float test = static_cast<float>(Random::get(static_cast<int>(bottomAngle), static_cast<int>(topAngle)));
    std::cout << topAngle << std::endl;
    std::cout << bottomAngle << std::endl;

    std::cout << test << std::endl;
    angle = test; // roughly pointing left
    return { pos, angle };
}

*/
/*
top
    constexpr float RAD_TO_DEG = 180.f / 3.14159265f;
    int side = Random::get(0, 3); // 0=top, 1=right, 2=bottom, 3=left
    side = 3;
    sf::Vector2f pos;
    float angle;

    pos = { static_cast<float>(Random::get(0, static_cast<float>(screenWidth))), 0.f };

    float bottomAngle = -std::atan(pos.x / screenHeight) * RAD_TO_DEG + 270;
    float topAngle = std::atan((screenWidth - pos.x) / screenHeight) * RAD_TO_DEG + 270; // this works
    angle = static_cast<float>(Random::get(static_cast<int>(bottomAngle), static_cast<int>(topAngle)));
    std::cout << topAngle << std::endl;
    std::cout << bottomAngle << std::endl;

*/


/*

    std::cout << pos.y << std::endl;
    // essentially changing the angle we are looking at to be 180 degrees and then calculating how much up and down from that angle we can go
    float topAngle = 180.f - (std::atan(pos.y / screenWidth) * RAD_TO_DEG);
    float bottomAngle = 180.f + (std::atan((screenHeight - pos.y) / screenWidth) * RAD_TO_DEG);
    std::cout << topAngle << std::endl;
    std::cout << bottomAngle << std::endl;
    angle = static_cast<float>(Random::get(static_cast<int>(topAngle), static_cast<int>(bottomAngle)));
    angle = static_cast<int>(bottomAngle);

*/

/*
* bottom
    pos = { static_cast<float>(Random::get(0, screenWidth)), static_cast<float>(screenHeight) };
    // essentially calculate the angle you would shoot out at zero degrees if the the two targets are 900,1600 then rotate it 90 degrees
    float topAngle = std::atan(pos.x / screenHeight) * RAD_TO_DEG + 90;
    float bottomAngle = -std::atan((screenWidth - pos.x) / screenHeight) * RAD_TO_DEG + 90; // this works
    angle = static_cast<float>(Random::get(static_cast<int>(bottomAngle), static_cast<int>(topAngle)));
    std::cout << topAngle << std::endl;
    std::cout << bottomAngle << std::endl;
*/



/*
* left side
    pos = { 0.f, static_cast<float>(Random::get(0, screenHeight)) };
    std::cout << pos.y << std::endl;
    float topAngle = std::atan(pos.y / screenWidth) * RAD_TO_DEG;
    float bottomAngle = -std::atan((screenHeight - pos.y) / screenWidth) * RAD_TO_DEG; // this works
    angle = static_cast<float>(Random::get(static_cast<int>(bottomAngle), static_cast<int>(topAngle)));
    std::cout << topAngle << std::endl;
    std::cout << bottomAngle << std::endl;
*/

// could switch to radians but degrees is more intuitive. Also easier to use with the randon number generator.
// repawn helper
std::pair<sf::Vector2f, float> SpawnInfo(int screenWidth, int screenHeight)
{
    constexpr float RAD_TO_DEG = 180.f / 3.14159265f;
    int side = Random::get(0, 3); // 0=top, 1=right, 2=bottom, 3=left
    sf::Vector2f pos;
    float angle;
    float bottomAngle;
    float topAngle;

    switch (side) {
    case 0: // top
        pos = { static_cast<float>(Random::get(0, screenWidth)), 0.f };
        bottomAngle = -std::atan(pos.x / screenHeight) * RAD_TO_DEG + 270;
        topAngle = std::atan((screenWidth - pos.x) / screenHeight) * RAD_TO_DEG + 270; // this works
        angle = static_cast<float>(Random::get(static_cast<int>(bottomAngle), static_cast<int>(topAngle)));

        std::cout << topAngle << std::endl;
        std::cout << bottomAngle << std::endl;

        break;
    case 1: // right

        pos = { static_cast<float>(screenWidth),  static_cast<float>(Random::get(0, screenHeight))};
        // essentially changing the angle we are looking at to be 180 degrees and then calculating how much up and down from that angle we can go
        topAngle = 180.f - (std::atan(pos.y / screenWidth) * RAD_TO_DEG);
        bottomAngle = 180.f + (std::atan((screenHeight - pos.y) / screenWidth) * RAD_TO_DEG);
        angle = static_cast<float>(Random::get(static_cast<int>(topAngle), static_cast<int>(bottomAngle)));

        std::cout << topAngle << std::endl;
        std::cout << bottomAngle << std::endl;

        break;
    case 2: // bottom

        pos = { static_cast<float>(Random::get(0, screenWidth)), static_cast<float>(screenHeight) };
        // essentially calculate the angle you would shoot out at zero degrees if the the two targets are 900,1600 then rotate it 90 degrees
        topAngle = std::atan(pos.x / screenHeight) * RAD_TO_DEG + 90;
        bottomAngle = -std::atan((screenWidth - pos.x) / screenHeight) * RAD_TO_DEG + 90; // this works
        angle = static_cast<float>(Random::get(static_cast<int>(bottomAngle), static_cast<int>(topAngle)));

        std::cout << topAngle << std::endl;
        std::cout << bottomAngle << std::endl;
        break;
    case 3: // left

        pos = { 0.f, static_cast<float>(Random::get(0, screenHeight)) };
        topAngle = std::atan(pos.y / screenWidth) * RAD_TO_DEG;
        bottomAngle = -std::atan((screenHeight - pos.y) / screenWidth) * RAD_TO_DEG; // this works
        angle = static_cast<float>(Random::get(static_cast<int>(bottomAngle), static_cast<int>(topAngle)));

        std::cout << topAngle << std::endl;
        std::cout << bottomAngle << std::endl;
        break;
    default:
        pos = { 0.f, 0.f };
        angle = 0;
    }

    return { pos, angle };
}


// setting up meteor intitally, when out of bounds, or when is destryoed
void Meteor::respawn()
{
    constexpr float DEG_TO_RAD = 3.14159265f / 180.f;
    float screenWidth{ 1600.f };
    float screenHeight{ 900.f };

    auto [pos, angle] = SpawnInfo(screenWidth, screenHeight);
    visual.setPosition(pos);
    hitBox.setPosition(pos);

    //
    std::cout << angle << std::endl;
    float xDirection = std::cos(angle * DEG_TO_RAD);
    float yDirection = std::sin(angle * DEG_TO_RAD);
    launchVelocity = { speed * xDirection, speed * -yDirection };

    velocity = { sf::Vector2f(0.f, 0.f) }; // set velocity to zero and wait for launch time
    health = 150; // reset health

    launchTime = launchClock.getElapsedTime().asSeconds() + Random::get(2, 10); // amount of seconds from now it will be shot out


    // set launch time probably set like global speed for all rocks and then divy that speed up for the x and y
//veleocities. maybe just get a random number thats a likea fraction or acutually made genreate a random angle
// between where you want it to shoot off then clac the sin cos of its x y velcoties

}