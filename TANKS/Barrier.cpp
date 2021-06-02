#include "Barrier.h"

Barrier::Barrier(int ax, int ay, int type, sf::Texture& texture)
{
    this->type = (Type)type; 

    //init sprite
    body.setTexture(texture);
    SetRect();
    body.setPosition(ax, ay); 
}

const sf::FloatRect Barrier::getBounds() const
{
    return this->body.getGlobalBounds();
}

void Barrier::render(sf::RenderTarget* target)
{
    target->draw(body);
}

bool Barrier::loseHp(Rotation bulletRotation, int damage)
{
    if (type % 2)
        return true; 
    if(type <= 2)
        Destroy(bulletRotation);
    hp -= damage;
    return hp > 0;
}

void Barrier::SetRect()
{
    switch (type)
    {
    case Barrier::IRON:
    case Barrier::BRICK:
        break;
    case Barrier::IRON_HF_V:
    case Barrier::BRICK_HF_V:
        body.setTextureRect(sf::IntRect(0, 0, 20, 40));
        break;
    case Barrier::IRON_HF_H:
    case Barrier::BRICK_HF_H:
        body.setTextureRect(sf::IntRect(0, 0, 40, 20));
        break;
    }
}

void Barrier::Destroy(Rotation bulRot)
{
    switch (bulRot)
    {
    case Rotation::RIGHT:
        body.move(20, 0); //40x40 picture; 
    case Rotation::LEFT:
        body.setTextureRect(sf::IntRect(0, 0, 20, 40));
        break;
    case Rotation::DOWN:
        body.move(0, 20);
    case Rotation::UP:
        body.setTextureRect(sf::IntRect(0, 0, 40, 20));
        break;
    }
}
