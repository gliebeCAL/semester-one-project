#ifndef DUNGEN_H
#define DUNGEN_H


class DunGen
{
    public:
        DunGen(int levelSizeX,int levelSizeY,int difficulty);
        //Does nothing

        void Generate(int levelSizeX,int levelSizeY,int difficulty);
        //Generates the level, The size of the level in the X direction, the size in the Y, the difficulty for the dungeons.
        //For later use, might want a tileset variable so that it can be swapped depending on the dungeon

        void TunnelCreate(int t);
        //Creates the tunnels
        //t is the integer from the for loop to decide which room to use

        void ResetLevel();
        //Sets all the values in the level back to 0.

        void TunnelUp(int t);
        //Goes Up

        void TunnelRight(int t);
        //Goes Right

        void TunnelDown(int t);
        //Goes Down

        void TunnelLeft(int t);
        //Goes Left

        virtual ~DunGen();
        //Does nothing

        int level[9999][9999];
        //The area where the level is stored.
    protected:
    private:
        int direction,roomTotal,pointSize, xCap,yCap;
        //Direction for the tunnel, amount of rooms, how large a point can be, the cap for x, the cap for y
        int roomSizeX,roomSizeY,xRoomMin,yRoomMin,xRoomCap,yRoomCap;
        //Sets the X and Y size of the room, sets the minimum and maximum X and Y size a room can be.
        int xRoomStartLoc,yRoomStartLoc;
        //Decides where a room starts at in the grid
        int roomCornerX[9999],roomCornerY[9999];
        //Finds the upper left and bottom right corner of each room
        int cornerCount = 0;
        //Counts the current corner
        int lastX,lastY;
        //Counts the last X and Y. Intended for the rooms for array
        int cornerAccess = 0;
        //Used to crawl through the corner arrays
        bool tunnelContact = false;
        //Checks if the tunnel has made contact with the point it was looking for.
        int tunnelX,tunnelY,prevTunDir;
        //Marks the current X and Y of the tunnel, marks the previous direction the tunnel was in
        int tunTopOrBot;
        //Decides if the tunnel goes on the top or the bottom
        bool firstTun = true;
        //Checks if it's the first tunnel in a direction. If it's true, it'll move forward twice unless it's at a hard cap.

};

#endif // DUNGEN_H
