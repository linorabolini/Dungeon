#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include "SpriteNode.hpp"
#include "Tile.hpp"
#include "TurnManager.hpp"
#include "GameManager.hpp"

using namespace std;

class Tile;
class TurnManager;
class Unit : public SpriteNode
{
public:
    sf::Vector2f position;
    Tile *tile = nullptr;

    void setTile(Tile* theTile);

    void doTurn();
    void setTurnManager(TurnManager* turnManager) { turnManager_ = turnManager; }
private:
    TurnManager* turnManager_;


// move it to a component ?
public:
    
    void receiveDamage(int damage) {
        hp_ = max(0, hp_ - damage);
    }
    int getHP() {
        return hp_;
    }
    void setHP(int value) {
        hp_ = value;
    }
private:
    int hp_;
};


#endif /* UNIT_HPP */
