#include <Unit.hpp>

void Unit::die() {
    // play dead animation or something here;
    // Unit controller die sequence

    // Locator::getGameManager()->removeUnit(this);
    dispose();
}