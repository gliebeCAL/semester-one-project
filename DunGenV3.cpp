#include "DunGen.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

DunGen::DunGen(int xCap,int yCap)
{
    Generate(xCap,yCap);
}

void DunGen::Generate(int xCap,int yCap)
{

    srand(time(NULL));

    Tunnels(xCap,yCap,5,3);

}

void DunGen::Tunnels(int xCap,int yCap,int difficulty,int roomType)
{
    //To do: Add an extra
    lineLength = 10;
    //Decides the size of the tunnel. This is actually one OVER what it should be (0-9, which is 10 digits.)
    tunX = rand() % (xCap+1);
    tunY = rand() % (yCap+1);

    levelXCap = xCap;
    levelYCap = yCap;

    level[tunX][tunY] = roomType;

    firstTunX = tunX;
    firstTunY = tunY;

    //while (tunCount<lineLength)
    for (int t=1;t<lineLength;t++)
    //Hm. I might need to make a long, elaborate scan to make sure it
    {
        tunCount = 0;

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
            level[tunX][tunY] = roomType;
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
                level[tunX][tunY] = roomType;
            }
        }

        //As a word of forethought, this is an extraordinarily bad method of generation.
        //Try to find a way to generate it properly.
        /*for (int x=0;x<= levelXCap;x++)
        {
            for (int y=0;y<=levelYCap;y++)
            {
                if (level[x][y] == 3)
                {
                    tunCount++;
                    //There's probably a more efficient way of doing this. But for now, this'll do.
                }
            }
        }*/


    }
    lastTunX = tunX;
    lastTunY = tunY;

    prevDir = 5;
}

void DunGen::Rooms(int xCap,int yCap,int difficulty,int roomType)
{

}

void DunGen::ResetLevel()
{
    for (int x=0;x<=100;x++)
    {
        for (int y=0;y<=100;y++)
        {
            level[x][y] = 0;
        }
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
