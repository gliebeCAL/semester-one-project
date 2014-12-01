#include <iostream>
#include <DunGen.h>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Melee_Enemy.h"

/*
Note to self:
Combat is implemented, need to work on multiple enemies, and make them spawn in the level.

Learn pointers. Do it.
*/

int main()
{
    bool dungeonGenerated = false;
    //Used to see if the dungeon is generated yet.
    bool playerSpawned = false;
    //Used to see if the player has been spawned yet.
    bool playerMoved = false;

    int melee_Enemies = 1;

    DunGen dungeon(10,10);
    Player pChar(50,50);


    Melee_Enemy mEnemy(1,0,0,1,1,1,10,10,dungeon.level);
    mEnemy.GenerateSprite();


    sf::View camera;
    camera.setSize(800,600);
    camera.setCenter(pChar.posX,pChar.posY);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Dirt and Dungeons");

    int levelSize = 0;


    dungeon.levelOccupied[pChar.posX][pChar.posY] = true;
    dungeon.levelOccupied[mEnemy.posX][mEnemy.posY] = true;

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
                            mEnemy.health = pChar.Attack(mEnemy.health);
                            playerMoved = true;
                            std::cout << "Enemy Health: " << mEnemy.health << std::endl;
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
                            mEnemy.health = pChar.Attack(mEnemy.health);
                            playerMoved = true;
                            std::cout << "Enemy Health: " << mEnemy.health << std::endl;
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
                            mEnemy.health = pChar.Attack(mEnemy.health);
                            playerMoved = true;
                            std::cout << "Enemy Health: " << mEnemy.health << std::endl;
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
                            mEnemy.health = pChar.Attack(mEnemy.health);
                            playerMoved = true;
                            std::cout << "Enemy Health: " << mEnemy.health << std::endl;
                        }
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
            dungeon.SpriteGenerate();

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

            if (mEnemy.enemyDeleted == true)
            {
                //Delete the enemy's positions.
                dungeon.levelOccupied[mEnemy.posX][mEnemy.posY] = false;
            }
            else
            {
                dungeon.levelOccupied[mEnemy.posX][mEnemy.posY] = false;
                mEnemy.AIAction(dungeon.levelOccupied,10,10,pChar.posX,pChar.posY,dungeon.level);
                dungeon.levelOccupied[mEnemy.posX][mEnemy.posY] = true;
                playerMoved = false;

                if (mEnemy.enemyCanAttack == true)
                {
                    pChar.health = mEnemy.Attack(pChar.health);
                    std::cout << "Player Health: " << pChar.health << std::endl;
                    mEnemy.enemyCanAttack = false;
                }

                if (mEnemy.health <= 0)
                {
                    dungeon.levelOccupied[mEnemy.posX][mEnemy.posY] = false;
                }
            }
        }

        /*for(int m=0;m<meleeEnemies;m++)
        {
            dungeon.levelOccupied[melee[m].posX][melee[m].posY] = true;
        }*/

        //So what these do is set what opts are occupied at the end of every loop.



        window.clear();
        window.draw(dungeon.level_sprite,40000,sf::Quads);
        window.draw(pChar.sprite);
        window.draw(mEnemy.sprite);
        window.display();
    }

    return 0;
}
