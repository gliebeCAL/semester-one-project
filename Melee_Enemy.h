#ifndef MELEE_ENEMY_H
#define MELEE_ENEMY_H

#include <Enemy.h>
#include <SFML/Graphics.hpp>



class Melee_Enemy : public Enemy
{
    public:
        Melee_Enemy(int difficulty,int spawnX, int spawnY,int aiType, int eType, int intelligence, int xCap, int yCap);
        void Create(int difficulty,int spawnX, int spawnY,int aiType, int eType, int intelligence, int xCap, int yCap);
        //Should get the constructor from it's parent.
        void AIAction(/*int level[],bool levelOccupied[],*/int xCap,int yCap,int playerposX, int playerposY);
        void GenerateSprite();
        sf::Sprite sprite;

        void MoveUp();
        void MoveDown(int yCap);
        void MoveLeft();
        void MoveRight(int xCap);
    protected:
    private:
        sf::Texture texture;
};

#endif // MELEE_ENEMY_H
