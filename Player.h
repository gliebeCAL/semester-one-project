#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player
{
    public:
        Player(int xSize,int ySize);
        void Spawn(int spawnX,int spawnY);
        //Should just be X's and Y's

        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();
        //These move it.

        int Attack(int eHealth);

        void AddToInventory();
        //Make an item class, so that I can make an inventory array.

        sf::Sprite sprite;
        int posX,posY;

        int health;
        //I'll probably need more things, like stats and inventory. But for now, this'll do.
    protected:
    private:
        sf::Texture texture;
        int attackpwr;
};

#endif // PLAYER_H
