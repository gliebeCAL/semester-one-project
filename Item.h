#ifndef ITEM_H
#define ITEM_H


class Item
{
    public:
        Item();
        void Generate(int type,int difficulty);

        void NameItem(int difficulty);
        void GenerateSprite();
        void GenerateEffects();
        //Shouldn't need to specify if it hurts you or not
        void GenerateSpells(bool offensive);
        //So damage (Fireball, etc) or buffs (Heal, more power, etc)
        //Should I make a class for enchantments and spells?


        string namePrefix1;
        string namePrefix2;
        string namePrefix3;
        string namePrefix4;
        string namePrefix5;
        string namePrefix6;
        string namePrefix7;
        //Stuff like Flaming,Frozen, Giant, Powerful, etc
        //Over 8 gets special prefixes, like Epic, Legendary, Master, Godly, etc
        string nameItem;
        //Sword, Axe, Spear, etc
        //Maybe some special types for bad weapons (Ex: if you should get 5-10 weapons and get a 0, call it a stick)
        string nameSuffix;
        //Of X

        int itemType;
        int damage;
        int defense;
        int itemSprite;
        int enchant = 0;
        int enchantRoll;
        int enchantEffect;

        int spell = 1;
        int spellRoll;
        int spellEffect;
    protected:
    private:
};

#endif // ITEM_H
