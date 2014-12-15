#ifndef MELEE_ENEMY_H
#define MELEE_ENEMY_H
#include <Enemy.h>
#include <SFML/Graphics.hpp>



class Melee_Enemy : public Enemy
{
    public:
        Melee_Enemy();
        Melee_Enemy(int difficulty,int spawnX, int spawnY,int aiType, int eType, int intelligence, int levelxCap, int levelyCap,int dun[100][100]);
        void Create(int difficulty,int spawnX, int spawnY,int aiType, int eType, int intelligence, int levelxCap, int levelyCap,int dun[100][100]);
        //Should get the constructor from it's parent.
        void AIAction(bool levelOccupied[100][100],int xCap,int yCap,int playerposX, int playerposY,int level[100][100]);
        void GenerateSprite();
        sf::Sprite sprite;

        void MoveUp(bool level_occupied[100][100],int level[100][100]);
        void MoveDown(int yCap,bool level_occupied[100][100],int level[100][100]);
        void MoveLeft(bool level_occupied[100][100],int level[100][100]);
        void MoveRight(int xCap,bool level_occupied[100][100],int level[100][100]);

        int Attack(int pHealth);

        int health;

        bool enemyCanAttack = false;
        bool enemyDeleted = false;
        bool enemyPosWipe = false;
    protected:
    private:
        sf::Texture texture;
        int attackpwr;
};

#endif // MELEE_ENEMY_H
