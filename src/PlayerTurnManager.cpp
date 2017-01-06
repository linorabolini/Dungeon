#include <PlayerTurnManager.hpp>

void PlayerTurnManager::doTurn(Unit *unit)
{
    // player can only do actions over the surrounding tiles.
    auto tile = unit->tile;
    auto surroundingTiles = tile->surroundingTiles;

    auto possibleActions = getUnitPossibleActions(unit, surroundingTiles);

    highlightTiles(possibleActions, surroundingTiles);

    auto actionToDo = waitForPlayerAction(possibleActions);

    highlightTiles(possibleActions, surroundingTiles, false);

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
        std::this_thread::yield();
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
                SpriteNode weapon(Locator::getResourceManager()->getTexture("weapon"));
                SpriteNode selectedEffect(Locator::getResourceManager()->getTexture("selectedTileEffect"));
                weapon.addChild(&selectedEffect);

                std::vector<float> pos = {0, 0};
                tween::Tween::make()
                    .to(pos, {-16.f, 0})
                    .fromTo(1.f, 2.f) // workaround to use onUpdate
                    .onUpdate([&](){
                        weapon.setPosition(pos[0], pos[1]);
                    })
                    .seconds(1);

                auto zoom = std::make_shared<float>(1.f);                
                tween::Tween::make()
                    .to(*zoom, 0.1f)
                    .onUpdate([](float zoom){
                        Locator::getGameManager()->getCamera()->setZoom(zoom);
                    })
                    .seconds(1)
                    .retain(zoom);

                unit->addChild(&weapon);

                WAIT(1000);

                // BATTLE PHASE

                // TODO: play weapon effects
                targetTile->unit->receiveDamage(10); // check if enemy dies and play dead anim TODO: create dead animations
                
                Font& font = Locator::getResourceManager()->getFont("Boo City");
                TextNode damageText("10", font, 100);
                damageText.setScale(0.1, 0.1);
                damageText.setPosition(2.5f, -8.f);
                targetTile->unit->addChild(&damageText);
                std::vector<float> textPos = {2.5f, -8.f};
                tween::Tween::make()
                    .to(textPos, {2.5f, -16.f})
                    .fromTo(1.f, 2.f) // workaround to use onUpdate
                    .onUpdate([&](){
                        damageText.setPosition(textPos[0], textPos[1]);
                    })
                    .easeoutsine()
                    .seconds(0.5);

                WAIT(1100);

                targetTile->unit->removeChild(&damageText);

                // END BATTLE PHASE

                unit->removeChild(&weapon);

                tween::Tween::make()
                    .to(*zoom, 1.f)
                    .onUpdate([](float zoom){
                        Locator::getGameManager()->getCamera()->setZoom(zoom);
                    })
                    .seconds(1)
                    .retain(zoom);

                WAIT(1100);
            };
        }
        else if (targetTile->GetPropertyString("solid") != "true")
        {
            actions[dir] = [=]() {
                LOG("MOVE TO TILE");
                unit->setTile(targetTile);
            };
        }
    }

    return actions;
}

void PlayerTurnManager::highlightTiles(std::map<Direction, UnitAction> possibleActions, std::map<Direction, Tile *> tiles, bool value)
{
    static SpriteNode effect(Locator::getResourceManager()->getTexture("selectedTileEffect"));

    for (auto &reg : possibleActions)
    {
        auto tile = tiles[reg.first];
        if (tile && tile->GetPropertyString("solid") != "true")
        {
            if (value)
            {
                tile->addChild(&effect);
            }
            else
            {
                tile->removeChild(&effect);
            }
        }
    }
}