#include <PlayerTurnManager.hpp>

void PlayerTurnManager::doTurn(Unit *unit)
{
    // player can only do actions over the surrounding tiles.
    auto tile = unit->tile;
    auto surroundingTiles = tile->surroundingTiles;

    auto possibleActions = getUnitPossibleActions(unit, surroundingTiles);

    highlightTiles(surroundingTiles);
    auto actionToDo = waitForPlayerAction(possibleActions);
    highlightTiles(surroundingTiles, false);

    actionToDo(unit);
}

UnitAction
PlayerTurnManager::waitForPlayerAction(std::map<Direction, UnitAction> possibleActions)
{
    LOG_AND_WAIT("SELECTING AN ACTION");
    while (true)
    {
        if (possibleActions.count(Direction::LEFT) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            return possibleActions[Direction::LEFT];
        }
        if (possibleActions.count(Direction::RIGHT) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            return possibleActions[Direction::RIGHT];
        }
        if (possibleActions.count(Direction::UP) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            return possibleActions[Direction::UP];
        }
        if (possibleActions.count(Direction::DOWN) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            return possibleActions[Direction::DOWN];
        }
    }
}

std::map<Direction, UnitAction>
PlayerTurnManager::getUnitPossibleActions(Unit *unit, std::map<Direction, Tile *> surroundingTiles)
{
    std::map<Direction, UnitAction> actions;
    for (auto &reg : surroundingTiles)
    {
        auto dir = reg.first;
        auto targetTile = reg.second;

        if (targetTile->unit)
        {
            actions[dir] = [targetTile](Unit *unit) {
                LOG_AND_WAIT("ATTACK !");
            };
        }
        else if (targetTile->GetPropertyString("solid") != "true")
        {
            actions[dir] = [targetTile](Unit *unit) {
                LOG_AND_WAIT("DUMMY ACTION");
                unit->setTile(targetTile);
            };
        }
    }

    return actions;
}

void PlayerTurnManager::highlightTiles(std::map<Direction, Tile *> tiles, bool value)
{
    for (auto &reg : tiles)
    {
        if (reg.second)
        {
            if (value)
            {
                reg.second->sprite.setColor(sf::Color(0, 255, 0));
            }
            else
            {
                reg.second->sprite.setColor(sf::Color::White);
            }
        }
    }
}