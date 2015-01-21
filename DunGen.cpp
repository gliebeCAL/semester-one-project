#include "DunGen.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>

DunGen::DunGen(int xCap,int yCap,int difficulty)
{
    Generate(xCap,yCap,difficulty);
}

void DunGen::Generate(int xCap,int yCap,int difficulty)
{

    srand(time(NULL));

    //blankTexture.loadFromFile("sprites/dungeon_sprites/emptytile.png");
    //lvlTexture.loadFromFile("sprites/dungeon_sprites/room.png");
    //stairTexture.loadFromFile("sprites/dungeon_sprites/dstair.png");

    ResetLevel();

    Tunnels(xCap,yCap,difficulty,3);

    Rooms(xCap,yCap,difficulty,4);

    PlaceChest(difficulty);

    SpriteGenerate();


}

void DunGen::Tunnels(int xCap,int yCap,int difficulty,int roomType)
{
    //To do: Add an extra
    lineLength = 20;
    //Decides the size of the tunnel. This is actually one OVER what it should be (0-9, which is 10 digits.). Replace with a formula later.
    tunX = rand() % (xCap+1);
    tunY = rand() % (yCap+1);

    levelXCap = xCap;
    levelYCap = yCap;

    level[tunX][tunY] = roomType;
    tunLocX[0] = tunX;
    tunLocY[0] = tunY;

    firstTunX = tunX;
    firstTunY = tunY;

    tunCount = 0;

    //while (tunCount<lineLength)
    for (int t=1;t<lineLength;t++)
    //Hm. I might need to make a long, elaborate scan to make sure it
    {

        direction = rand()% 3;

        if (prevDir == 5)
        {
            direction = rand() % 4;

            if (direction == 0)
            {
                std::cout << "Start 0" << std::endl;
                TunUp();
            }
            else if (direction == 1)
            {
                std::cout << "Start 1" << std::endl;
                TunRight();
            }
            else if (direction == 2)
            {
                std::cout << "Start 2" << std::endl;
                TunDown();
            }
            else if (direction == 3)
            {
                std::cout << "Start 3" << std::endl;
                TunLeft();
            }

        }
        else if (prevDir == 0)
        {
            std::cout << "Previous Direction 0: ";
            if (direction == 0)
            {
                std::cout << "Standard Up" << std::endl;
                TunUp();
            }
            else if (direction == 1)
            {
                std::cout << "Standard Right" << std::endl;
                TunRight();
            }
            else if (direction == 2)
            {
                std::cout << "Standard Left" << std::endl;
                TunLeft();
            }
        }
        else if (prevDir == 1)
        {
            std::cout << "Previous Direction 1: ";
            if (direction == 0)
            {
                std::cout << "Standard Up" << std::endl;
                TunUp();
            }
            else if (direction == 1)
            {
                std::cout << "Standard Right" << std::endl;
                TunRight();
            }
            else if (direction == 2)
            {
                std::cout << "Standard Down" << std::endl;
                TunDown();
            }

        }
        else if (prevDir == 2)
        {
            std::cout << "Previous Direction 2: ";
            if (direction == 0)
            {
                std::cout << "Standard Right" << std::endl;
                TunRight();
            }
            else if (direction == 1)
            {
                std::cout << "Standard Down" << std::endl;
                TunDown();
            }
            else if (direction == 2)
            {
                std::cout << "Standard Left" << std::endl;
                TunLeft();
            }

        }
        else if (prevDir == 3)
        {
            std::cout << "Previous Direction 3: ";
            if (direction == 0)
            {
                std::cout << "Standard Up" << std::endl;
                TunUp();
            }
            else if (direction == 1)
            {
                std::cout << "Standard Down" << std::endl;
                TunDown();
            }
            else if (direction == 2)
            {
                std::cout << "Standard Left" << std::endl;
                TunLeft();
            }

        }
        if (roomType > level[tunX][tunY])
        {
            tunCount++;
            level[tunX][tunY] = roomType;
            tunLocX[t] = tunX;
            tunLocY[t] = tunY;
        }

        if (direction != prevDir)
        {
            //This process will create some extra space, between -1 to 2 spots.
            t++;

            std::cout << "Double Down: ";
            if (direction == 0)
            {
                std::cout << "Up" << std::endl;
                TunUp();
                prevDir = 0;
            }
            else if (direction == 1)
            {
                std::cout << "Right" << std::endl;
                TunRight();
                prevDir = 1;
            }
            else if (direction == 2)
            {
                std::cout << "Down" << std::endl;
                TunDown();
                prevDir = 2;
            }
            else if (direction == 3)
            {
                std::cout << "Left" << std::endl;
                TunLeft();
                prevDir = 3;
            }

            if (roomType > level[tunX][tunY])
            {
                tunCount++;
                level[tunX][tunY] = roomType;
                tunLocX[t] = tunX;
                tunLocY[t] = tunY;
            }
        }
    }
    lastTunX = tunX;
    lastTunY = tunY;

    prevDir = 5;
}

void DunGen::Rooms(int xCap,int yCap,int difficulty,int roomType)
{
    std::cout << "INITIATE ROOM CREATION" << std::endl;

    roomTotal = 4;
    //So the formula probably has something to do with rand and difficulty, plus a flat 2 at the end (Beginning and end)
    //Again, is actually 1 over intended.

    rWidth = 3;
    rHeight = 3;
    //Again, will be random for now. But this will do.
    startXDist = rand() % (rWidth);
    startYDist = rand() % (rHeight);
    //For this, 0-2. Figures out the distance between the upper left of the room and the tunnel.

    roomFX = firstTunX - startXDist;
    roomFY = firstTunY - startYDist;
    roomLX = roomFX + rWidth;
    roomLY = roomFY + rHeight;


    //These four make sure rooms are never off the map.

    RoomBoundsCheck(xCap,yCap);

    firstRoomULX = roomFX;
    firstRoomULY = roomFY;
    firstRoomLRX = roomLX;
    firstRoomLRY = roomLY;

    for (int rx=roomFX;rx<roomLX;rx++)
    {
        for (int ry=roomFY;ry<roomLY;ry++)
        {
            if (level[rx][ry] < roomType)
            {
                level[rx][ry] = roomType;
            }
        }
    }

    //Last room
    rWidth = 3;
    rHeight = 3;
    //Again, will be random for now. But this will do.
    startXDist = rand() % (rWidth);
    startYDist = rand() % (rHeight);
    //For this, 0-2. Figures out the distance between the upper left of the room and the tunnel.

    roomFX = lastTunX - startXDist;
    roomFY = lastTunY - startYDist;
    roomLX = roomFX + rWidth;
    roomLY = roomFY + rHeight;


    //These four make sure rooms are never off the map.
    //To do: Dedicate this map to the array.

    /*
    It seems it's not fond of me throwing double nested loops.
    Or maybe it's the override it doesn't like?
    //No, scratch all of that. It overrides just fine, it loops a nested loop fine. What seems to be
    //the problem is that the initial variable can't equal another variable? And a while loop causes a crash.
    //Hm.
    */
    RoomBoundsCheck(xCap,yCap);

    lastRoomULX = roomFX;
    lastRoomULY = roomFY;
    lastRoomLRX = roomLX;
    lastRoomLRY = roomLY;

    for (int rx=roomFX;rx<roomLX;rx++)
    {
        for (int ry=roomFY;ry<roomLY;ry++)
        {
            if (level[rx][ry] < roomType)
            {
                level[rx][ry] = roomType;
            }
        }
    }


    for(int r=1;r<roomTotal;r++)
    {
        //Makes the rest of the rooms.
        rWidth = 3;
        rHeight = 3;
        //Will be random later.

        startXDist = rand()%rWidth;
        startYDist = rand()%rHeight;
        //Should have a count of the amount of the tunnels.
        roomXInv = rand()%2;
        roomYInv = rand()%2;

        if (roomXInv == 1)
        {
            startXDist = (startXDist)*-1;
        }
        if (roomYInv == 1)
        {
            startYDist = (startYDist)*-1;
        }

        roomFX = tunLocX[rand()%(tunCount-1)+1] + startXDist;
        roomFY = tunLocY[rand()%(tunCount-1)+1] + startYDist;
        //So any room but the first and last.

        roomLX = roomFX + rWidth;
        roomLY = roomFX + rHeight;

        RoomBoundsCheck(xCap,yCap);

        for (int rx=roomFX;rx<roomLX;rx++)
        {
            for (int ry=roomFY;ry<roomLY;ry++)
            {
                if (level[rx][ry] < roomType)
                {
                    level[rx][ry] = roomType;
                }
            }
        }

    }

    //Makes stairs (Spawn point for the player)
    startStairX = rand()%(firstRoomLRX - firstRoomULX)+firstRoomULX;
    startStairY = rand()%(firstRoomLRY - firstRoomULY)+firstRoomULY;
    level[startStairX][startStairY] = 5;

    endStairX = rand()%(lastRoomLRX - lastRoomULX)+lastRoomULX;
    endStairY = rand()%(lastRoomLRY - lastRoomULY)+lastRoomULY;
    level[endStairX][endStairY] = 6;
}

void DunGen::PlaceChest(int difficulty)
{
    int chesttotal = rand()%(difficulty) + 1;
    //The highest difficulty is about 20, I think, so the most you could have is 5.
    int chestX = rand()%levelXCap;
    int chestY = rand()%levelYCap;


    for(int c=0;c<chesttotal;c++)
    {
        chestTexture[c].loadFromFile("sprites/dungeon_sprites/chest.png");

        while (level[chestX][chestY] != 4 and level[chestX][chestY] == false)
        {

            //So to leave this loop, the point has to be a 4 and the occupation has to be false.

            //Make sure it's on 4 a and doesn't overlap with other chests.
            chestX = rand()%levelXCap;
            chestY = rand()%levelYCap;
        }

        chestLocX[c] = chestX;
        chestLocY[c] = chestY;
        chestsActive++;

        chestSprite[c].setTexture(chestTexture[c],false);
        chestSprite[c].setPosition(chestX*50,chestY*50);

        chestOccupied[chestX][chestY] = true;
    }
}

void DunGen::Load(int xCap,int yCap)
{
    ResetLevel();

    levelXCap = xCap;
    levelYCap = yCap;

    //Also load from file
    //Scratched. Just here for historical purposes.
}

void DunGen::ResetLevel()
{
    for (int x=0;x<=100;x++)
    {
        for (int y=0;y<=100;y++)
        {
            level[x][y] = 0;
            levelOccupied[x][y] = false;
            //chestOccupied[x][y] = false;
        }
    }

    /*chest0Created = false;
    chest1Created = false;
    chest2Created = false;
    chest3Created = false;
    chest4Created = false;*/

    for (int l=0;l<levelSize;l++)
    {
        level_sprite[l] = sf::Vector2f(0,0);
    }
}


void DunGen::TunUp()
{
    if (tunY <= 0 or (level[tunX][tunY-1] == 3 and (level[tunX+1][tunY] != 3 or level[tunX-1][tunY] != 3)))
    {
        altDir = rand() % 2;

        if (altDir == 0)
        {
            TunRight();
        }
        else if (altDir == 1)
        {
            TunLeft();
        }

    }
    else
    {
        tunY -= 1;
        direction = 0;
    }
}

void DunGen::TunRight()
{
    if (tunX >= levelXCap or (level[tunX+1][tunY] == 3 and (level[tunX][tunY+1] != 3 or level[tunX][tunY-1] != 3)))
    {
        altDir = rand() % 2;

        if (altDir == 0)
        {
            TunUp();
        }
        else if (altDir == 1)
        {
            TunDown();
        }

    }
    else
    {
        tunX += 1;
        direction = 1;
    }
}

void DunGen::TunDown()
{
    if (tunY >= levelYCap or (level[tunX][tunY + 1] == 3 and (level[tunX+1][tunY] != 3 or level[tunX-1][tunY] != 3)))
    {
        altDir = rand() % 2;

        if (altDir == 0)
        {
            TunRight();
        }
        else if (altDir == 1)
        {
            TunLeft();
        }

    }
    else
    {
        tunY += 1;
        direction = 2;
    }

}

void DunGen::TunLeft()
{
    if (tunX == 0 or (level[tunX - 1][tunY] == 3 and (level[tunX][tunY+1] != 3 or level[tunX][tunY-1] != 3)))
    {
        //First part checks the cap, second checks if the spot is occupied by a tile and if the spot is
        altDir = rand() % 2;

        if (altDir == 0)
        {
            TunUp();
        }
        else if (altDir == 1)
        {
            TunDown();
        }

    }
    else
    {
        tunX -= 1;
        direction = 3;
    }

}

void DunGen::RoomBoundsCheck(int xCap,int yCap)
{
    if (roomFX < 0)
    {
        roomLX -= roomFX;
        roomFX -= roomFX;
        //So -15 - (-15) = 0
    }

    if (roomLX > xCap)
    {
        roomFX -= roomLX - xCap;
        roomLX -= roomLX - xCap;
    }

    if (roomFY < 0)
    {
        roomLY -= roomFY;
        roomFY -= roomFY;
        //So like, -5 - -5 would be 0.
    }

    if (roomLY > yCap)
    {
        roomFY -= roomLY - yCap;
        roomLY -= roomLY - yCap;
    }
}

void DunGen::SpriteGenerate()
{
    for (int y=0;y<=levelYCap;y++)
    {
        for (int x=0;x<=levelXCap;x++)
        {
            std::cout << level[x][y] << ", ";

            if (level[x][y] == 0)
            {
                //sprite[x][y].setTexture(blankTexture,false);

                level_sprite[levelSize] = sf::Vector2f(x*50,y*50);
                level_sprite[levelSize].color = sf::Color::Green;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50));
                level_sprite[levelSize].color = sf::Color::Green;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Green;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50),(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Green;

                levelSize++;
                //That pseudo code should do it.


                //Oh boy. This'll be about 5000 pixels. Well, camera's easy enough to do with the player. Maybe I'll put the
                //the player in the first 3 or 4 space I can find. Or last. Whatever.
                //And let's see. Maybe make a color code? 2 and 3 don't exist, player is blue, 0 is green 4 is red, 3 is...whatever's left. White?
                //I suppose the game loop will check if the player can or can't go to a certain spot.

            }
            /*
            else if (level[x][y] == 1)
            {
                level_sprite[levelSize] = sf::Vector2f(x*50,y*50);
                level_sprite[levelSize].color = sf::Color::Black;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50));
                level_sprite[levelSize].color = sf::Color::Black;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Black;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50),(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Black;

                levelSize++;

            }
            else if (level[x][y] == 2)
            {
                level_sprite[levelSize] = sf::Vector2f(x*50,y*50);
                level_sprite[levelSize].color = sf::Color::Cyan;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50));
                level_sprite[levelSize].color = sf::Color::Cyan;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Cyan;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50),(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Cyan;

                levelSize++;

            }*/
            else if (level[x][y] == 3)
            {
                //sprite[x][y].setTexture(lvlTexture,false);
                level_sprite[levelSize] = sf::Vector2f(x*50,y*50);
                level_sprite[levelSize].color = sf::Color::Yellow;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50));
                level_sprite[levelSize].color = sf::Color::Yellow;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Yellow;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50),(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Yellow;

                levelSize++;
            }
            else if (level[x][y] == 4)
            {
                //sprite[x][y].setTexture(lvlTexture,false);
                level_sprite[levelSize] = sf::Vector2f(x*50,y*50);
                level_sprite[levelSize].color = sf::Color::Red;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50));
                level_sprite[levelSize].color = sf::Color::Red;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Red;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50),(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Red;

                levelSize++;
            }
            else if (level[x][y] == 5)
            {
                //sprite[x][y].setTexture(lvlTexture,false);
                level_sprite[levelSize] = sf::Vector2f(x*50,y*50);
                level_sprite[levelSize].color = sf::Color::Blue;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50));
                level_sprite[levelSize].color = sf::Color::Blue;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Blue;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50),(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Blue;

                levelSize++;
            }
            else if (level[x][y] == 6)
            {
                //sprite[x][y].setTexture(stairTexture,false);
                level_sprite[levelSize] = sf::Vector2f(x*50,y*50);
                level_sprite[levelSize].color = sf::Color::Magenta;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50));
                level_sprite[levelSize].color = sf::Color::Magenta;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50)+50,(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Magenta;

                levelSize++;

                level_sprite[levelSize] = sf::Vector2f((x*50),(y*50)+50);
                level_sprite[levelSize].color = sf::Color::Magenta;

                levelSize++;

            }

            /*if (chestOccupied[x][y] == true)
            {
                //Draw a chest in that area
                if (chest0Created == false)
                {
                    chest0Created = true;
                }
                else if (chest1Created == false)
                {
                    chest1Created = true;
                }
                else if (chest2Created == false)
                {
                    chest2Created = true;
                }
                else if (chest3Created == false)
                {
                    chest3Created = true;
                }
                else if (chest4Created == false)
                {
                    chest4Created = true;
                }
            }*/
        }
    std::cout << std::endl;
    }
}
