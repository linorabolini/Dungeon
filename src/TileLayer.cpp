#include <TileLayer.hpp>

void TileLayer::connectTiles(int rows, int cols) {
    for (int i = 0; i < tiles.size(); i++)
    {

        auto& tile = tiles[i];
        int col = (i % cols);
        int row = (i / cols);

        if(col == 0)
        {
            cout << endl;
        }

        auto isSolid = tile.GetPropertyString("solid") == "true" ? 1 : 0;
        cout << isSolid;

        tile.surroundingTiles[Direction::LEFT] = col > 0 ? &tiles[i - 1] : nullptr;
        tile.surroundingTiles[Direction::RIGHT] = col < cols - 1 ? &tiles[i + 1] : nullptr;
        tile.surroundingTiles[Direction::UP] = row > 0 ? &tiles[i - cols] : nullptr;
        tile.surroundingTiles[Direction::DOWN] = row < rows - 1 ? &tiles[i + cols] : nullptr;
    }
    cout << endl;
}

Tile& TileLayer::getTile(int index) {
    return tiles[index];
}
