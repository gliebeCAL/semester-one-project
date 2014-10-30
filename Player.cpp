#include "Player.h"
#include <SFML/Graphics.hpp>

Player::Player(int xSize,int ySize)
{
    texture.loadFromFile("rat_bot_final.png");
    sprite.setTexture(texture,false);
    //Static texture, so false.
    //Needs to be adjusted so it points to an actual sprite.

    //These two are temporary, to set the value of posX and posY
    posX = 0;
    posY = 0;
}

void Player::Spawn(int spawnX,int spawnY)
{
    sprite.setPosition(sf::Vector2f(spawnX*50,spawnY*50));
    posX = spawnX;
    posY = spawnY;
    //These are what is drawn I think, so these get the actual pixel
    //value.
}

void Player::MoveUp()
{
    sprite.move(0,-50);
    posY -= 1;
}

void Player::MoveDown()
{
    sprite.move(0,50);
    posY += 1;
}

void Player::MoveLeft()
{
    sprite.move(-50,0);
    posX -= 1;
}

void Player::MoveRight()
{
    sprite.move(50,0);
    posX += 1;
}
