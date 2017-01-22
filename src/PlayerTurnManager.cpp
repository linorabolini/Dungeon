#include <PlayerTurnManager.hpp>

#include "NodeTween.hpp"


void PlayerTurnManager::doTurn(Unit* unit, Board* board)
{
    auto tile = board->getUnitTile(unit);
    TilesByDirection surroundingTiles = tile->surroundingTiles;
    // player can only do actions over the surrounding tiles.
    auto possibleActions = getUnitPossibleActions(unit, board);

    highlightTiles(possibleActions, surroundingTiles);

    auto actionToDo = waitForPlayerAction(possibleActions);

    if (!actionToDo)
    { // when screen exists
        return;
    }

    highlightTiles(possibleActions, surroundingTiles, false);

    (*actionToDo)();
}

UnitAction *
PlayerTurnManager::waitForPlayerAction(UnitActionsByDirection &possibleActions)
{
    LOG("SELECTING AN ACTION");
    auto gm = Locator::getGameManager();
    while (!gm->isGameFinished())
    {
        for (auto &reg : possibleActions)
        {
            auto dir = dirToKeyboard_[reg.first];
            if (dir && sf::Keyboard::isKeyPressed(dir))
            {
                return &possibleActions[reg.first];
            }
        }
        std::this_thread::yield();
    }
    return nullptr;
}

UnitActionsByDirection
PlayerTurnManager::getUnitPossibleActions(Unit *unit, Board* board)
{
    auto tile = board->getUnitTile(unit);
    TilesByDirection surroundingTiles = tile->surroundingTiles;
    UnitActionsByDirection actions;
    for (auto &reg : surroundingTiles)
    {
        auto dir = reg.first;
        auto targetTile = reg.second;

        // COMMAND PATTERN
        Unit* tileUnit = board->getTileUnit(targetTile);
        if (tileUnit)
        {
            Unit& sourceUnit = *unit;
            Unit& targetUnit = *tileUnit;
            actions[dir] = [&]() {
                auto camera = Locator::getGameManager()->getCamera();

                SpriteNode weapon(Locator::getResourceManager()->getTexture("weapon"));
                SpriteNode selectedEffect(Locator::getResourceManager()->getTexture("selectedTileEffect"));
                weapon.addChild(&selectedEffect);

                std::vector<float> pos = {0, 0};
                NodeTween::position(weapon, pos, {-16.f, 0})
                    .easeoutsine()
                    .seconds(1);

                tween::Tween::make()
                    .to(camera->targetZoom, 0.1f)
                    .seconds(1);

                sourceUnit.addChild(&weapon);

                WAIT(1000);

                // BATTLE PHASE

                // TODO: play weapon effects
                targetUnit.receiveDamage(10); // check if enemy dies and play dead anim TODO: create dead animations

                Font &font = Locator::getResourceManager()->getFont("Boo City");
                TextNode damageText("10", font, 100);
                damageText.setScale(0.1, 0.1);
                damageText.setPosition(2.5f, -8.f);
                sourceUnit.addChild(&damageText);
                std::vector<float> textPos = {2.5f, -8.f};
                NodeTween::position(damageText, textPos, {2.5f, -16.f})
                    .easeoutsine()
                    .seconds(0.5);

                WAIT(1100);

                sourceUnit.removeChild(&damageText);

                // END BATTLE PHASE

                sourceUnit.removeChild(&weapon);

                tween::Tween::make()
                    .to(camera->targetZoom, 1.f)
                    .seconds(1);

                WAIT(1100);
            };
        }
        else if (targetTile->GetPropertyString("solid") != "true")
        {
            actions[dir] = [=]() {
                LOG("MOVE TO TILE");
                board->setUnitTile(unit, targetTile);
            };
        }
    }

    return actions;
}

void PlayerTurnManager::highlightTiles(UnitActionsByDirection &possibleActions, TilesByDirection tiles, bool value)
{
    static SpriteNode effect(Locator::getResourceManager()->getTexture("selectedTileEffect"));

    for (auto &reg : possibleActions)
    {
        auto tile = tiles[reg.first];
        if (tile->GetPropertyString("solid") != "true")
        {
            if (value)
            {
                tile->addChild(&effect, true);
            }
            else
            {
                tile->removeChild(&effect);
            }
        }
    }
}