#include <iostream>
#include <DunGen.h>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Melee_Enemy.h"

/*
Note to self:
Multi-Combat is implemented. Prob need same thing for casters and archers.

Learn pointers. Do it.

Need to adjust how enemies are removed

Okay, so! List of things to do:

Load fixed map
    -Should make a fixed map or somtehing.

Change levels
    -Need to erase the sprites, then remake and replace.

Add inventory
    -Need to figure out text I guess.

Add weapons
Add spells
Add chests
Add HUD elements

Add different enemies

Options Menu

Title Screen
*/


int main()
{
    bool dungeonGenerated = false;
    //Used to see if the dungeon is generated yet.
    bool playerSpawned = false;
    //Used to see if the player has been spawned yet.
    bool playerMoved = false;

    int melee_Enemies = 3;

    int enemyPosX;
    int enemyPosY;
    bool enemyGenerated = false;

    DunGen dungeon(10,10);
    Player pChar(50,50);

    Melee_Enemy mEnemy[50];



    //Melee_Enemy mEnemy(1,0,0,1,1,1,10,10,dungeon.level);


    sf::View camera;
    camera.setSize(800,600);
    camera.setCenter(pChar.posX,pChar.posY);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Dirt and Dungeons");

    int levelSize = 0;


    dungeon.levelOccupied[pChar.posX][pChar.posY] = true;
    dungeon.levelOccupied[mEnemy[0].posX][mEnemy[0].posY] = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                //This moves the character.
                //Outstanding bugs:
                //Can't move when you're in the level.
                //Can move while on a point that is 0.
                //
                if (event.key.code == sf::Keyboard::D)
                {
                    if (dungeon.level[pChar.posX + 1][pChar.posY] > 0 and pChar.posX < dungeon.levelXCap)
                    {
                        if (dungeon.levelOccupied[pChar.posX+1][pChar.posY] == false)
                        {
                            dungeon.levelOccupied[pChar.posX][pChar.posY] = false;
                            pChar.MoveRight();
                            dungeon.levelOccupied[pChar.posX][pChar.posY] = true;
                            playerMoved = true;
                        }
                        else
                        {
                            for(int m=0;m<melee_Enemies;m++)
                            {
                                if (mEnemy[m].posX == pChar.posX+1 and mEnemy[m].posY == pChar.posY)
                                {
                                    mEnemy[m].health = pChar.Attack(mEnemy[m].health);
                                    playerMoved = true;
                                    std::cout << "Enemy " << m <<" Health: " << mEnemy[m].health << std::endl;
                                }
                            }
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    if (dungeon.level[pChar.posX - 1][pChar.posY] > 0 and pChar.posX > 0)
                    {
                        if (dungeon.levelOccupied[pChar.posX-1][pChar.posY] == false)
                        {
                            dungeon.levelOccupied[pChar.posX][pChar.posY] = false;
                            pChar.MoveLeft();
                            dungeon.levelOccupied[pChar.posX][pChar.posY] = true;
                            playerMoved = true;
                        }
                        else
                        {
                            for(int m=0;m<melee_Enemies;m++)
                            {
                                if (mEnemy[m].posX == pChar.posX-1 and mEnemy[m].posY == pChar.posY)
                                {
                                    mEnemy[m].health = pChar.Attack(mEnemy[m].health);
                                    playerMoved = true;
                                    std::cout << "Enemy " << m <<" Health: " << mEnemy[m].health << std::endl;
                                }
                            }
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::S)
                {
                    if (dungeon.level[pChar.posX][pChar.posY + 1] > 0 and pChar.posY < dungeon.levelXCap)
                    {
                        if (dungeon.levelOccupied[pChar.posX][pChar.posY+1] == false)
                        {
                            dungeon.levelOccupied[pChar.posX][pChar.posY] = false;
                            pChar.MoveDown();
                            dungeon.levelOccupied[pChar.posX][pChar.posY] = true;
                            playerMoved = true;
                        }
                        else
                        {
                            for(int m=0;m<melee_Enemies;m++)
                            {
                                if (mEnemy[m].posX == pChar.posX and mEnemy[m].posY == pChar.posY+1)
                                {
                                    mEnemy[m].health = pChar.Attack(mEnemy[m].health);
                                    playerMoved = true;
                                    std::cout << "Enemy " << m <<" Health: " << mEnemy[m].health << std::endl;
                                }
                            }
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    if (dungeon.level[pChar.posX][pChar.posY - 1] > 0 and pChar.posY > 0)
                    {
                        if (dungeon.levelOccupied[pChar.posX][pChar.posY-1] == false)
                        {
                            dungeon.levelOccupied[pChar.posX][pChar.posY] = false;
                            pChar.MoveUp();
                            dungeon.levelOccupied[pChar.posX][pChar.posY] = true;
                            playerMoved = true;
                        }
                        else
                        {
                            for(int m=0;m<melee_Enemies;m++)
                            {
                                if (mEnemy[m].posX == pChar.posX and mEnemy[m].posY == pChar.posY-1)
                                {
                                    mEnemy[m].health = pChar.Attack(mEnemy[m].health);
                                    playerMoved = true;
                                    std::cout << "Enemy " << m <<" Health: " << mEnemy[m].health << std::endl;
                                }
                            }
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::Space)
                {
                    if (pChar.posX == dungeon.endStairX and pChar.posY == dungeon.endStairY)
                    {
                        dungeon.Generate(4,4);
                    }
                }
                if (event.key.code == sf::Keyboard::Period)
                {
                    playerMoved = true;
                }
            }
        }
        if (dungeonGenerated == false)
        {
            levelSize = 0;
            //I feel like I should make this a shape in the DunGen class. I'll figure it out later.

            for (int m=0;m<melee_Enemies;m++)
            {
                while (enemyGenerated == false)
                {
                    enemyPosX = rand() % (dungeon.levelXCap+1);
                    enemyPosY = rand() % (dungeon.levelYCap+1);

                    if (dungeon.levelOccupied[enemyPosX][enemyPosY] == false and dungeon.level[enemyPosX][enemyPosY] == 4)
                    {
                        mEnemy[m].Create(1,enemyPosX,enemyPosY,1,1,1,10,10,dungeon.level);
                        dungeon.levelOccupied[enemyPosX][enemyPosY] = true;
                        enemyGenerated = true;
                    }
                }

                enemyGenerated = false;

                //Find a value that isn't occupied and is a 4.
                mEnemy[m].GenerateSprite();
            }

            dungeonGenerated = true;
        }
        if (playerSpawned == false)
        {
            pChar.Spawn(dungeon.startStairX,dungeon.startStairY);
            //Will later be used to place the player at the spawn location, but that's not implemented yet.
            playerSpawned = true;
        }



        camera.setCenter(pChar.posX*50,pChar.posY*50);
        window.setView(camera);

        if (playerMoved == true)
        {
            for (int mE=0;mE<melee_Enemies;mE++)
            {
                if (mEnemy[mE].enemyDeleted == true)
                {
                    //Delete the enemy's positions.
                    dungeon.levelOccupied[mEnemy[mE].posX][mEnemy[mE].posY] = false;
                }
                else
                {
                    dungeon.levelOccupied[mEnemy[mE].posX][mEnemy[mE].posY] = false;
                    mEnemy[mE].AIAction(dungeon.levelOccupied,10,10,pChar.posX,pChar.posY,dungeon.level);
                    dungeon.levelOccupied[mEnemy[mE].posX][mEnemy[mE].posY] = true;
                    playerMoved = false;

                    if (mEnemy[mE].enemyCanAttack == true)
                    {
                        pChar.health = mEnemy[mE].Attack(pChar.health);
                        std::cout << "Player Health: " << pChar.health << std::endl;
                        mEnemy[mE].enemyCanAttack = false;
                    }

                    if (mEnemy[mE].health <= 0)
                    {
                        dungeon.levelOccupied[mEnemy[mE].posX][mEnemy[mE].posY] = false;
                    }
                }
            }
        }

        //So what these do is set what opts are occupied at the end of every loop.

        window.clear();
        window.draw(dungeon.level_sprite,40000,sf::Quads);
        window.draw(pChar.sprite);
        for (int m=0;m<melee_Enemies;m++)
        {
            window.draw(mEnemy[m].sprite);
        }
        window.display();
    }

    return 0;
}
