#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include "SpriteNode.hpp"

using namespace std;

class Tile;
class Unit : public SpriteNode
{
public:

// move it to a component ?
public:
    
    // delegate to component
    void receiveDamage(int damage) {
        hp_ = max(0, hp_ - damage);

        if(hp_ == 0) {
            die(); 
        }
    }
    void die();

    int getHP() {
        return hp_;
    }
    void setHP(int value) {
        hp_ = value;
    }

    virtual bool isDead() { return hp_ == 0; }
private:
    int hp_ = 0;
};


#endif /* UNIT_HPP */
