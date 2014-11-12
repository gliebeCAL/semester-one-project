#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>

class Enemy
{
    public:
        //Enemy(int difficulty,int spawnX, int spawnY,int aiType, int eType, int intelligence, int xCap, int yCap);
        void Create(int difficulty,int spawnX, int spawnY,int aiType, int eType, int intelligence, int xCap, int yCap);

        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();
        //Need to check if the area is a 0, if it's off the screen, and if the spot is occupied.
        void GenerateSprite();

        virtual ~Enemy();

        int posX,posY;
        int diff;
        int health;
        int intell;
        int xCap, yCap;
        int tiebreak;
        //Add a sight so it'll know how far it can see?
        sf::Sprite sprite;
    protected:
    private:
};

#endif // ENEMY_H
