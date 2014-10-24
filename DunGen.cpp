#include "DunGen.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

//Crashes on Dungeon Generation occasionally. It works, though.
//Quick reminder that there are no random generating formulas, either.

DunGen::DunGen(int xCap,int yCap)
{
    Generate(xCap,yCap);
}

void DunGen::Generate(int xCap,int yCap)
{

    srand(time(NULL));

    Tunnels(xCap,yCap,5,3);

    Rooms(xCap,yCap,5,4);

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
    //To do: Dedicate this map to the array.

    /*
    It seems it's not fond of me throwing double nested loops.
    Or maybe it's the override it doesn't like?
    //No, scratch all of that. It overrides just fine, it loops a nested loop fine. What seems to be
    //the problem is that the initial variable can't equal another variable? And a while loop causes a crash.
    //Hm.
    */
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
