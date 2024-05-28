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
        for (int x = 0; x < line.size(); ++x) {
            // Décoder les types de tuiles à partir du fichier
            bool isEmpty = (line[x] == '0');
            bool isMonsterPath = (line[x] == '1');
            bool isMonsterBegin = (line[x] == '2');
            bool isMonsterEnd = (line[x] == '3');
            bool isTowerEmplacement = (line[x] == '4');
            bool isDecoration = (line[x] == '5');
            bool isTurnRight = (line[x] == '6');
            bool isTurnLeft = (line[x] == '7');

            setTileType(x, y, isEmpty, isMonsterPath, isMonsterBegin, isMonsterEnd, isTowerEmplacement, isDecoration, isTurnRight, isTurnLeft);
        }
        y++;
    }
}
