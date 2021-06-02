#ifndef BARRIER_H
#define BARRIER_H
#include<SFML/Graphics.hpp>
#include"definecells.h"

class Barrier
{
public:
    static enum Type : int
    {
        IRON = 1, BRICK, IRON_HF_V, BRICK_HF_V, IRON_HF_H, BRICK_HF_H
    };

    Barrier(int ax, int ay, int type, sf::Texture& texture);
    //functions
    void render(sf::RenderTarget* target);
    bool loseHp(Rotation bulletRotation, int damage = 1);
private:
    //    variables
    int hp;
    Type type;

    //  elements
    sf::Sprite body; 

    //  fun 
    void SetRect();
    void Destroy(Rotation bulRot);
};

#endif // BARRIER_H