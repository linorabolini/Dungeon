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

    actionToDo();
}

UnitAction
PlayerTurnManager::waitForPlayerAction(std::map<Direction, UnitAction> possibleActions)
{
    LOG("SELECTING AN ACTION");
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

        // COMMAND PATTERN 
        if (targetTile->unit)
        {
            actions[dir] = [=]() {
                Locator::getGameManager()->getCamera()->setZoom(0.05f);
                LOG("ATTACK !");
                LOG("PIM !");
                LOG("PAM !");
                LOG("PUM !");
                WAIT(1000);
                Locator::getGameManager()->getCamera()->setZoom(0.2f);
            };
        }
        else if (targetTile->GetPropertyString("solid") != "true")
        {
            actions[dir] = [=]() {
                LOG("DUMMY ACTION");
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