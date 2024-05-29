#include "./ModelH/Map.h"

Map::Map(int width, int height) : width(width), height(height) {
    tiles = vector<vector<Tile>>(width, vector<Tile>(height));
}

Map::~Map() {}

void Map::setTileType(int x, int y, bool isEmpty, bool isMonsterPath, bool isMonsterBegin, bool isMonsterEnd, bool isTowerEmplacement, bool isDecoration, bool isTurnRight, bool isTurnLeft) {
    tiles[x][y].isEmpty = isEmpty;
    tiles[x][y].isMonsterPath = isMonsterPath;
    tiles[x][y].isMonsterBegin = isMonsterBegin;
    tiles[x][y].isMonsterEnd = isMonsterEnd;
    tiles[x][y].isTowerEmplacement = isTowerEmplacement;
    tiles[x][y].isDecoration = isDecoration;
    tiles[x][y].isTurnRight = isTurnRight;
    tiles[x][y].isTurnLeft = isTurnLeft;
}

Tile Map::getTile(int x, int y) const {
    return tiles[x][y];
}

vector<vector<Tile>> Map::getTiles() const {
    return tiles;
}


int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

void Map::createMap(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open file " << filename << endl;
        return;
    }

    string line;
    int y = 0;
    while (getline(file, line)) {
        for (long long unsigned int x = 0; x < line.size(); ++x) {
            // Créer une instance temporaire de Tile
            Tile tile;
            
            // Décoder les types de tuiles à partir du fichier
            if (line[x] == '2') {
                tile.isMonsterBegin = true;
                tile.isMonsterPath = true;
            } else if (line[x] == '3') {
                tile.isMonsterEnd = true;
                tile.isMonsterPath = true;
            } else if (line[x] == '6') {
                tile.isTurnRight = true;
                tile.isEmpty = true;
            } else if (line[x] == '7') {
                tile.isTurnLeft = true;
                tile.isEmpty = true;
            } else {
                tile.isEmpty = (line[x] == '0');
                tile.isMonsterPath = (line[x] == '1');
                tile.isTowerEmplacement = (line[x] == '4');
                tile.isDecoration = (line[x] == '5');
            }
            
            // Définir le type de tuile dans la grille
            setTileType(x, y, tile.isEmpty, tile.isMonsterPath, tile.isMonsterBegin, tile.isMonsterEnd, tile.isTowerEmplacement, tile.isDecoration, tile.isTurnRight, tile.isTurnLeft);
        }
        y++;
    }
}
