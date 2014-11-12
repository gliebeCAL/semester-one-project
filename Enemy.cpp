#include "Enemy.h"

/*Enemy::Enemy(int difficulty,int spawnX, int spawnY,int aiType, int eType, int intelligence, int xCap, int yCap)
{
    Create(difficulty,spawnX,spawnY,aiType,eType,intelligence,xCap,yCap);
}*/

void Enemy::Create(int difficulty,int spawnX, int spawnY,int aiType, int eType, int intelligence, int lvlxCap, int lvlyCap)
{
    posX = spawnX;
    posY = spawnY;
    xCap = lvlxCap;
    yCap = lvlyCap;

    diff = difficulty;

    intell = intelligence;
    //ctor
    if (aiType == 1)
    {
        //Melee
        health = 20;
        //For now, AI dictates sprite. I'll change it later.
    }
    else if (aiType == 2)
    {
        //Mage
    }
    else if (aiType == 3)
    {
        //Archer
    }
}

void Enemy::MoveUp()
{
    if (posY < 0)
    {
        //These check if the area is occupied by something.
        sprite.move(0,-50);
        posY -= 1;
    }
}

void Enemy::MoveDown()
{
    if (posY < yCap)
    {
        sprite.move(0,50);
        posY += 1;
    }
}

void Enemy::MoveLeft()
{
    if (posX > 0)
    {
        sprite.move(-50,0);
        posX -= 1;
    }
}

void Enemy::MoveRight()
{
    if (posX < xCap)
    {
        sprite.move(50,0);
        posX += 1;
    }
}

void Enemy::GenerateSprite()
{

}

Enemy::~Enemy()
{
    //dtor
}
