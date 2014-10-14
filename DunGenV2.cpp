#include "DunGen.h"
#include <stdlib.h>
#include <time.h>

//Note to self: I need to seed the rand at some point.

/*
5-Last Room
4-Room
3-Tunnel
2-Bonus Room
1-Bonus Tunnel
0-Nothing

0-Up
1-Right
2-Down
3-Left
*/

DunGen::DunGen(int levelSizeX,int levelSizeY,int difficulty)
{
    srand (time(NULL));
    //Sets seed for randomizing
    ResetLevel();
    //Sets all the level to 0 so it can be drawn.
    Generate(levelSizeX,levelSizeY,difficulty);
    //Generates the level when it's created. The level can be regenerated again by running reset, then
    //generate again.

}

void DunGen::Generate(int levelSizeX,int levelSizeY,int difficulty)
{

    xCap = levelSizeX + 1;
    yCap = levelSizeY + 1;
    //Sets the size that the room can NOT go through. It starts at 0,0.

    xRoomCap = 5;
    yRoomCap = 5;
    xRoomMin = 3;
    yRoomMin = 3;
    //Temporary values for now.


    roomTotal = 4;
    //For temporary measures. Set an actual formula for this later.
    for(int r=1;r<=roomTotal;r++)
    {
        //Generates the rooms

        roomSizeX = rand() % (xRoomCap - xRoomMin) + xRoomMin;
        roomSizeY = rand() % (yRoomCap - yRoomMin) + yRoomMin;
        //Temporarily disabled because I don't have a formula for setting those yet.
        xRoomStartLoc = rand() % xCap;
        yRoomStartLoc = rand() % yCap;

        if (xRoomStartLoc > (xCap - roomSizeX))
        {
            //If the X is greater than the cap plus the X size, set it to that value.
            xRoomStartLoc = xCap - roomSizeX;

        }
        if (yRoomStartLoc > (yCap - roomSizeY))
        {
            //If the Y is greater than the cap plus the Y size
            yRoomStartLoc = yCap - roomSizeY;
        }

        roomCornerX[cornerCount] = xRoomStartLoc;
        roomCornerY[cornerCount] = yRoomStartLoc;
        cornerCount++;
        roomCornerX[cornerCount] = (xRoomStartLoc + roomSizeX);
        roomCornerY[cornerCount] = (yRoomStartLoc + roomSizeY);
        cornerCount++;
        //Marks the corners of the room

        //Creates the room size
        if (r==roomTotal)
        {
            //If this is the last room to be made, make it an end room.
            for(int rx=0;rx<=roomSizeX;rx++)
            {
                for(int ry=0;ry<=roomSizeY;ry++)
                {
                    //Fills all units in the coordinates with 5
                    level[rx][ry] = 5;
                }
            }
        }
        else
        {
            //If not, just make a standard room
            for(int rx=0;rx<=roomSizeX;rx++)
            {
                for(int ry=0;ry<=roomSizeY;ry++)
                {
                    //Fills all units in the coordinates with 4
                    level[rx][ry] = 4*r;
                }
            }
        }
    }

    for(int t=1;t<roomTotal;t++)
    {
        //Generates the tunnels
        //Chooses the first point
        tunnelX = rand() % (roomCornerX[t+1] - roomCornerX[t] + 1) + roomCornerX[t];

        if (tunnelX == roomCornerX[t])
        {
            //If tunnelX is on the left side
            tunnelY = rand() % (roomCornerY[t+1] - roomCornerY[t] + 1) + roomCornerY[t];
            prevTunDir = 3;
        }
        else if (tunnelX == roomCornerX[t+1])
        {
            //If tunnelX is the right side
            tunnelY = rand() % (roomCornerY[t+1] - roomCornerY[t] + 1) + roomCornerY[t];
            prevTunDir = 1;
        }
        else
        {
            tunTopOrBot = rand() % 2;
            //0 or 1
            if (tunTopOrBot == 0)
            {
                tunnelY = roomCornerY[t];
                prevTunDir = 0;
            }
            else if (tunTopOrBot == 1)
            {
                tunnelY = roomCornerY[t+1];
                prevTunDir = 2;
            }
        }

        //Makes the tunnels
        while(tunnelContact == false)
        {
            //Keep looping so long as the tunnel hasn't made contact with what it wants to hit.
            if (tunnelX + 1 >= roomCornerX[t+2] or tunnelX - 1 <= roomCornerX[t+3])
            {
                //If the tunnel is next to the desired room, we're done here, tunnels done.
                if (tunnelY >= roomCornerY[t+2] or tunnelY <= roomCornerY[t+3])
                {
                    tunnelContact = true;
                }
                else
                {
                    //Runs normally otherwise.
                    TunnelCreate(t);
                }
            }
            else if (tunnelY + 1 >= roomCornerY[t+2] and tunnelY - 1 <= roomCornerY[t+3])
            {
                if (tunnelX >= roomCornerX[t+2] or tunnelX <= roomCornerX[t+3])
                {
                    //The way these are set up ensure it will never get to a corner and stop.
                    tunnelContact = true;
                }
                else
                {
                    //Runs normally otherwise.
                    TunnelCreate(t);

                }

            }
            else
            {

            }
        }

        cornerAccess++;
        tunnelContact = false;
    }



}

void DunGen::TunnelCreate(int t)
{
    //I'm starting to think the functions need functions.

    //Made in to a function for legitimate reasons (AKA I'm going to reuse this like four time)
    direction = rand() % 5;
    //0-4, see top to see what 0-3 are for. 4 is to give the tunnel a bias towards going to the next room.
    if (tunnelX < roomCornerX[t+2])
    {
        //May need number examination
        //If the room is to the right
        if (prevTunDir == 0)
        {
            if (direction == 1 or direction == 2 or direction == 4)
            {
                TunnelRight(t);
            }
            else if (direction == 0)
            {
                TunnelUp(t);
            }
            else if (direction == 3)
            {
                TunnelLeft(t);
            }
        }

        else if (prevTunDir == 1)
        {
            //Needs values adjusted
            //Copied!

            if (direction == 1 or direction == 3 or direction == 4)
            {
                TunnelRight(t);
            }
            else if (direction == 2)
            {
                TunnelDown(t);
            }
            else if (direction == 0)
            {
                TunnelUp(t);
            }
        }

        else if (prevTunDir == 2)
        {
            //Needs values adjusted
            //Copied! x2

            if (direction == 1 or direction == 0 or direction == 4)
            {
                TunnelRight(t);
            }
            else if (direction == 2)
            {
                //Goes Down
                TunnelDown(t);

            }
            else if (direction == 3)
            {
                TunnelLeft(t);
            }
        }

        else if (prevTunDir == 3)
        {
            //This one's probably gonna have to be special, since it
            //goes in the opposite direction.
            if (direction == 3)
            {
                TunnelLeft(t);
            }
            else if (tunnelY < roomCornerY[t+2])
            {
                if (direction == 1 or direction == 2 or direction == 4)
                {
                    TunnelDown(t);
                }
                else if (direction == 0)
                {
                    TunnelUp(t);
                }

            }
            else if (tunnelY > roomCornerY[t+3])
            {
                if (direction == 0 or direction == 1 or direction == 4)
                {
                    TunnelUp(t);
                }
                else if (direction == 2)
                {
                    TunnelDown(t);
                }
            }
            else
            {
                if (direction == 0 or direction == 1)
                {
                    TunnelUp(t);
                }
                else if (direction == 2 or direction == 4)
                {
                    TunnelDown(t);
                }
            }

        }
    }
    else if (tunnelX > roomCornerX[t+3])
    {
        if (prevTunDir == 0)
        {
            if (direction == 3 or direction == 2 or direction == 4)
            {
                TunnelLeft(t);
            }
            else if (direction == 0)
            {
                TunnelUp(t);
            }
            else if (direction == 1)
            {
                TunnelRight(t);
            }
        }
        else if (prevTunDir == 1)
        {
            //Unique
            if (direction == 1)
            {
                TunnelRight(t);
            }
            else if (tunnelY < roomCornerY[t+2])
            {
                if (direction == 2 or direction == 3 or direction == 4)
                {
                    TunnelDown(t);
                }
                else if (direction == 0)
                {
                    TunnelUp(t);
                }

            }
            else if (tunnelY > roomCornerY[t+3])
            {
                if (direction == 0 or direction == 3 or direction == 4)
                {
                    TunnelUp(t);
                }
                else if (direction == 2)
                {
                    TunnelDown(t);
                }

            }
        }
        else if (prevTunDir == 2)
        {
            if (direction == 3 or direction == 0 or direction == 4)
            {
                TunnelLeft(t);
            }
            else if (direction == 2)
            {
                TunnelDown(t);
            }
            else if (direction == 1)
            {
                TunnelRight(t);
            }
        }
        else if (prevTunDir == 3)
        {
            if (direction == 3 or direction == 1 or direction == 4)
            {
                TunnelLeft(t);
            }
            else if (direction == 0)
            {
                TunnelUp(t);
            }
            else if (direction == 2)
            {
                TunnelDown(t);
            }
        }
    }

    else if (tunnelX > roomCornerX[t+2] and tunnelX < roomCornerX[t+3])
    {
        //If it's between the room's X's.
        if (tunnelY < roomCornerY[t+2])
        {
            if (prevTunDir == 0)
            {
                //Unique
                if (direction == 0)
                {
                    TunnelUp(t);
                }
                //There two are temporary measures, because I can't think of anything.
                else if (direction == 1 or direction == 2)
                {
                    TunnelRight(t);
                }
                else if (direction == 3 or direction == 4)
                {
                    TunnelLeft(t);
                }
            }
            else if (prevTunDir == 1)
            {
                if (direction == 2 or direction == 3 or direction == 4)
                {
                    TunnelDown(t);
                }
                else if (direction == 1)
                {
                    TunnelRight(t);
                }
                else if (direction == 0)
                {
                    TunnelUp(t);
                }
            }
            else if (prevTunDir == 2)
            {
                if (direction == 2 or direction == 0 or direction == 4)
                {
                    TunnelDown(t);
                }
                else if (direction == 1)
                {
                    TunnelRight(t);
                }
                else if (direction == 3)
                {
                    TunnelLeft(t);
                }
            }
            else if (prevTunDir == 3)
            {
                if (direction == 2 or direction == 1 or direction == 4)
                {
                    TunnelDown(t);
                }
                else if (direction == 0)
                {
                    TunnelUp(t);
                }
                else if (direction == 3)
                {
                    TunnelLeft(t);
                }
            }
        }

        else if (tunnelY > roomCornerY[t+3])
        {
            if (prevTunDir == 0)
            {
                if (direction == 0 or direction == 2 or direction == 4)
                {
                    TunnelUp(t);
                }
                else if (direction == 1)
                {
                    TunnelRight(t);
                }
                else if (direction == 3)
                {
                    TunnelLeft(t);
                }
            }
            else if (prevTunDir == 1)
            {
                if (direction == 0 or direction == 3 or direction == 4)
                {
                    TunnelUp(t);
                }
                else if (direction == 1)
                {
                    TunnelRight(t);
                }
                else if (direction == 2)
                {
                    TunnelDown(t);
                }

            }
            else if (prevTunDir == 2)
            {
                //Unique
                if (direction == 2)
                {
                    TunnelDown(t);
                }
                else if (direction == 0 or direction == 1)
                {
                    TunnelRight(t);
                }
                else if (direction == 3 or direction == 4)
                {
                    TunnelLeft(t);
                }

            }
            else if (prevTunDir == 3)
            {
                if (direction == 0 or direction == 1 or direction == 4)
                {
                    TunnelUp(t);
                }
                else if (direction == 2)
                {
                    TunnelDown(t);
                }
                else if (direction == 3)
                {
                    TunnelLeft(t);
                }
            }
        }
    }
    //Commits the changes and makes further changes if needed.
    if (level[tunnelX][tunnelY] < 3)
    {
        //Commits the change
        level[tunnelX][tunnelY] = 3;
    }

    if (tunnelX >= roomCornerX[t+2] and tunnelX <= roomCornerX[t+3] and
        tunnelY >= roomCornerY[t+2] and tunnelY <= roomCornerY[t+3])
    {
        //Checks if the tunnel makes contact with the room.
        tunnelContact = true;
    }

    if (direction != prevTunDir and tunnelContact == false)
    {
        //If
        if (direction == 0)
        {
            TunnelUp(t);
        }
        else if (direction == 1)
        {
            TunnelRight(t);
        }
        else if (direction == 2)
        {
            TunnelDown(t);
        }
        else if (direction == 3)
        {
            TunnelLeft(t);
        }

        direction = prevTunDir;

        if (level[tunnelX][tunnelY] < 3)
        {
            //Commits the changes again
            level[tunnelX][tunnelY] = 3;
        }
    }
    if (tunnelX >= roomCornerX[t+2] and tunnelX <= roomCornerX[t+3] and
        tunnelY >= roomCornerY[t+2] and tunnelY <= roomCornerY[t+3])
    {
        //Checks if the tunnel makes contact with the room again.
        tunnelContact = true;
    }

}

void DunGen::ResetLevel()
{
    for(int x=0;x<9999;x++)
    {
        for(int y=0;y<9999;y++)
        {
            level[x][y] = 0;
        }
    }
}

void DunGen::TunnelUp(int t)
{
    if (tunnelY == 0)
    {
        if (tunnelX > roomCornerX[t+3])
        {
            tunnelX -= 1;
            direction = 3;
        }
        else if (tunnelX < roomCornerX[t+2])
        {
            tunnelX += 1;
            direction = 1;
        }
    }
    else
    {
        tunnelY -= 1;
        direction = 0;
    }

}

void DunGen::TunnelRight(int t)
{
    if (tunnelX == xCap)
    {
        if (tunnelY < roomCornerY[t+2])
        {
            tunnelY += 1;
            direction = 2;
        }
        else if (tunnelY > roomCornerY[t+3])
        {
            tunnelY -= 1;
            direction = 1;
        }
    }
    else
    {
        tunnelX += 1;
        direction = 1;
    }

}

void DunGen::TunnelDown(int t)
{
    if (tunnelY == yCap)
    {
        if (tunnelX > roomCornerX[t+3])
        {
            tunnelX -= 1;
            direction = 3;
        }
        else if (tunnelX < roomCornerX[t+2])
        {
            tunnelX += 1;
            direction = 1;
        }
    }
    else
    {
        tunnelY += 1;
        direction = 2;
    }

}

void DunGen::TunnelLeft(int t)
{
    if (tunnelX == 0)
    {
        if (tunnelY < roomCornerY[t+2])
        {
            tunnelY += 1;
            direction = 2;
        }
        else if (tunnelY > roomCornerY[t+3])
        {
            tunnelY -= 1;
            direction = 0;
        }

    }
    else
    {
        tunnelX -= 1;
        direction = 3;
    }

}

DunGen::~DunGen()
{
    //dtor
}
