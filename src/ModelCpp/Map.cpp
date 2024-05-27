#include "./ModelH/Map.h"

Map::~Map() {
}

void Map::setTileType(int x, int y, TileType type) {
    tiles[x][y] = type;
}

TileType Map::getTileType(int x, int y) {
    return tiles[x][y];
}

int Map::getWidth() {
    return width;
}

int Map::getHeight() {
    return height;
}

void Map::createMap(string& filename) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open file " << filename << endl;
        return;
    }

    tiles.clear();

    string line;
    while (getline(file, line)) {
        vector<TileType> row;
        for (char c : line) {
            TileType type;
            switch (c) {
                case '0':
                    type = TileType::EMPTY;
                    break;
                case '1':
                    type = TileType::DECORATION;
                    break;
                case '2':
                    type = TileType::MONSTER_PATH;
                    break;
                case '3':
                    type = TileType::TOWER_EMPLACEMENT;
                    break;
                default:
                    cout << "Error: invalid cell type " << c << endl;
                    type = TileType::EMPTY; // Utilisation d'une valeur par défaut
                    break;
            }
            row.push_back(type);
        }
        tiles.push_back(row);
    }
}