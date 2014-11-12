#include "Melee_Enemy.h"
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include "Enemy.h"
#include <iostream>

Melee_Enemy::Melee_Enemy(int difficulty,int spawnX,int spawnY,int aiType,int eType,int intelligence,int levelxCap,int levelyCap)
{
    //ctor
    Create(difficulty,spawnX,spawnY,aiType,eType,intelligence,xCap,yCap);
}

void Melee_Enemy::Create(int difficulty,int spawnX,int spawnY,int aiType, int eType,int intelligence,int levelxCap,int levelyCap)
{
    posX = spawnX;
    posY = spawnY;
    xCap = levelxCap;
    yCap = levelyCap;

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

void Melee_Enemy::AIAction(/*int level[],bool levelOccupied[],*/int xCap,int yCap,int playerposX, int playerposY)
{
    //Note to self, include redirection and stuff if against a wall.
    std::cout << "AI Run" << std::endl;
    srand(time(NULL));

    if (intell == 1)
    {
        std::cout << "intell = 1" << std::endl;
        //Lowest intelligence, flat bumrush the player.
        //Omni-directional sight, because there's only one sprite.
        if ((posX + 3 >= playerposX and posX - 3 <= playerposX) and (posY + 3 >= playerposY and posY - 3 <= playerposY))
        {
            std::cout << "Player in range" << std::endl;
            //If the player is near you
            if ((posX + 1 == playerposX or posX - 1 == playerposX) and (posY == playerposY))
            {
                //Actually miscalibrated. It only reacts if you are diagonal to it.
                std::cout << "Player in melee range" << std::endl;
                //Do attack-y things.
            }
            else if ((posX == playerposX) and (posY+1 == playerposY or posY-1 == playerposY))
            {
                std::cout << "Player in melee range" << std::endl;
            }
            else
            {
                std::cout << "Move to player" << std::endl;
                //Okay, so: it gets this far, so at some point it goofs.

                if (posX > playerposX and posY > playerposY)
                {
                    std::cout << "Player is to the upper left" << std::endl;
                    //Player is at... Upper Left
                    if (posX - playerposX > posY - playerposY)
                    {
                        //If the distance from the left is greater than the distance from the up
                        MoveLeft();
                    }
                    else if (posX - playerposX < posY - playerposY)
                    {
                        //If it is further up then it is to the left
                        MoveUp();
                    }
                    else
                    {
                        //If they're equal, flip a coin
                        tiebreak = rand()%2;

                        if (tiebreak == 0)
                        {
                            MoveLeft();
                        }
                        else if (tiebreak == 1)
                        {
                            MoveUp();

                        }
                    }

                }
                else if (posX < playerposX and posY > playerposY)
                {
                    std::cout << "Player is to the upper right" << std::endl;
                    //Upper Right
                    if (playerposX - posX > posY - playerposY)
                    {
                        //If the distance from the right is greater than the distance from the up
                        MoveRight(xCap);
                    }
                    else if (playerposX - posX < posY - playerposY)
                    {
                        //If it is further up then it is to the right
                        MoveUp();
                    }
                    else
                    {
                        //If they're equal.
                        tiebreak = rand()%2;

                        if (tiebreak == 0)
                        {
                            MoveRight(xCap);
                        }
                        else if (tiebreak == 1)
                        {
                            MoveUp();

                        }
                    }

                }
                else if (posX > playerposX and posY < playerposY)
                {
                    std::cout << "Player is to the lower left" << std::endl;
                    //Lower Left
                    if (posX - playerposX > playerposY - posY)
                    {
                        //If the distance from the left is greater than the distance from the down
                        MoveLeft();
                    }
                    else if (posX - playerposX < playerposY - posY)
                    {
                        //If it is further down then it is to the left
                        MoveDown(yCap);
                    }
                    else
                    {
                        //If they're equal.
                        tiebreak = rand()%2;

                        if (tiebreak == 0)
                        {
                            MoveLeft();
                        }
                        else if (tiebreak == 1)
                        {
                            MoveDown(yCap);
                        }
                    }

                }
                else if (posX < playerposX and posY < playerposY)
                {
                    std::cout << "Player is to the lower right" << std::endl;
                    //Lower Right
                    if (playerposX - posX > playerposY - posY)
                    {
                        std::cout << "Move to the right." << std::endl;
                        //If the distance from the right is greater than the distance from the down
                        MoveRight(xCap);
                    }
                    else if (playerposX - posX < playerposY - posY)
                    {
                        std::cout << "Move down." << std::endl;
                        //If it is further down then it is to the right
                        MoveDown(yCap);
                        //Looks like the problem has to do with the actual movement functions.
                    }
                    else
                    {
                        //If they're equal.
                        tiebreak = rand()%2;

                        if (tiebreak == 0)
                        {
                            MoveRight(xCap);
                        }
                        else if (tiebreak == 1)
                        {
                            MoveDown(yCap);
                        }
                    }

                }
                else if (posX > playerposX and posY == playerposY)
                {
                    std::cout << "Player is to the left" << std::endl;
                    //Left
                    MoveLeft();
                }
                else if (posX < playerposX  and posY == playerposY)
                {
                    std::cout << "Player is to the right" << std::endl;
                    //Right
                    MoveRight(xCap);
                }
                else if (posX == playerposX and posY > playerposY)
                {
                    std::cout << "Player is to the top" << std::endl;
                    //Up
                    MoveUp();
                }
                else if (posX == playerposX and posY < playerposY)
                {
                    std::cout << "Player is to the bottom" << std::endl;
                    //Down
                    MoveDown(yCap);
                }

            }

        }
    }
    else if (intell == 2)
    {
        //Difficulty based actions
    }
    else if (intell >= 3)
    {
        //Does things based on difficulty.
    }
}

void Melee_Enemy::GenerateSprite()
{
    texture.loadFromFile("rat_bot_final.png");
    sprite.setTexture(texture, false);
    sprite.setPosition(posX*50,posY*50);
}


void Melee_Enemy::MoveUp()
{
    std::cout << "Up Move Function Accessed." << std::endl;
    if (posY > 0)
    {
        //These check if the area is occupied by something.
        std::cout << "Mobilization Upwards!" << std::endl;
        sprite.move(0,-50);
        posY -= 1;
    }
}

void Melee_Enemy::MoveDown(int yCap)
{
    std::cout << "Down Move Function Accessed." << std::endl;
    if (posY < yCap)
    {
        //So it's HERE where the AI breaks.
        std::cout << "Mobilization Downwards!" << std::endl;
        sprite.move(0,50);
        posY += 1;
    }
}

void Melee_Enemy::MoveLeft()
{
    std::cout << "Left Move Function Accessed." << std::endl;
    if (posX > 0)
    {
        std::cout << "Mobilization Left!" << std::endl;
        sprite.move(-50,0);
        posX -= 1;
    }
}

void Melee_Enemy::MoveRight(int xCap)
{
    std::cout << "Right Move Function Accessed." << std::endl;
    std::cout << posX << " " << posY << std::endl;
    std::cout << xCap << " " << yCap << std::endl;
    if (posX < xCap)
    {
        //xCap and yCap aren't getting the right values for some reason.
        //Only down and right seem to not work or something?
        std::cout << "Mobilization Right!" << std::endl;
        sprite.move(50,0);
        posX += 1;
    }
}
