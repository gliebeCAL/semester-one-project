#ifndef DUNGEN_H
#define DUNGEN_H

//Is still called just DunGen.

class DunGen
{
    public:
        DunGen(int xCap,int yCap);
        //Is, for the most part, useless. Just runs Generate  down there.
        //But if I don't have it run something when it starts, it breaks on me.
        void Generate(int xCap,int yCap);
        //This one just runs Tunnels and Rooms to generate the level.
        void Tunnels(int xCap,int yCap,int difficulty,int roomType);
        //Creats the tunnel. Well, I probably shouldn't have made it plural.
        //Remember! 3 is standard, 1 is bonus!
        void Rooms(int xCap,int yCap,int difficulty,int roomType);
        //Creates the rooms. Plurality is totally okay here.
        //Remember, 4 is standard, 2 is bonus!

        void ResetLevel();
        //Sets every part of the level to 0.

        void TunUp();
        void TunRight();
        void TunDown();
        void TunLeft();
        //Makes the tunnel. These might require adjustment for the bonus levels, specifically, so that the room check isn't
        //for just 3. The decision on what it should check for is up for debate (0? If it's lower?)

        int level[100][100];
    protected:
    private:
        int lineLength;
        //Chooses the Length of the tunnel
        int tunX;
        //Tunnel's X position
        int tunY;
        //Tunnel's Y position
        int direction;
        //Gets the direction of the line
        int prevDir = 5;
        //gets the previous direction
        int levelXCap,levelYCap;
        //Sets the caps on the level
        int altDir;
        //Sets alternate directions.
        int tunCount = 0;
        //Counts how many 3s there are in the area.
        int firstTunX,firstTunY,lastTunX,lastTunY;
        //Gets the first position and last position of the tunnel for room generation.

        int roomTotal;
        //Counts how many rooms there are.
};

#endif // DUNGEN_H
