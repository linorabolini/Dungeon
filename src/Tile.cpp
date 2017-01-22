#include <Tile.hpp>

bool Tile::isConnectedTo(Tile& other) {
    for(auto& reg : surroundingTiles) {
        if(&other == reg.second) {
            return true;
        }
    }

    return false;
}