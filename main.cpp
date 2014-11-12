#include <iostream>
#include <DunGen.h>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Melee_Enemy.h"

/*
Note to self:
Melee enemy is prototypically done (Need to implement stats, hitting, staying in the boundary, but it moves and
                                    follows you.)
*/

int main()
{
    bool dungeonGenerated = false;
    //Used to see if the dungeon is generated yet.
    bool playerSpawned = false;
    //Used to see if the player has been spawned yet.
    bool playerMoved = false;

    DunGen dungeon(10,10);
    Player pChar(50,50);
    Melee_Enemy mEnemy(1,0,0,1,1,1,10,10);
    mEnemy.GenerateSprite();


    sf::View camera;
    camera.setSize(800.f,600.f);
    camera.setCenter(pChar.posX,pChar.posY);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Dirt and Dungeons");

    int levelSize = 0;


    //This should go in the loop.

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
                        pChar.MoveRight();
                        playerMoved = true;
                    }
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    if (dungeon.level[pChar.posX - 1][pChar.posY] > 0 and pChar.posX > 0)
                    {
                        pChar.MoveLeft();
                        playerMoved = true;
                    }
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    if (dungeon.level[pChar.posX][pChar.posY + 1] > 0 and pChar.posY < dungeon.levelXCap)
                    {
                        pChar.MoveDown();
                        playerMoved = true;
                    }
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    if (dungeon.level[pChar.posX][pChar.posY - 1] > 0 and pChar.posY > 0)
                    {
                        pChar.MoveUp();
                        playerMoved = true;
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
            mEnemy.AIAction(10,10,pChar.posX,pChar.posY);
            playerMoved = false;
        }



        window.clear();
        window.draw(dungeon.level_sprite,40000,sf::Quads);
        window.draw(pChar.sprite);
        window.draw(mEnemy.sprite);
        window.display();
    }

    return 0;
}
