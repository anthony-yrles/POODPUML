#include "./ModelH/Map.h"

Map::Map(int width, int height, int fileWidth, int fileHeight, const string& filename) : width(width), height(height), fileWidth(fileWidth), fileHeight(fileHeight) {
    // Ouvrir le fichier map.txt
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open file " << filename << endl;
        return;
    }

    // Déterminer les dimensions du fichier map.txt
    string line;
    while (getline(file, line)) {
        fileWidth = line.size(); // La largeur correspond à la taille de la ligne
        fileHeight++; // Compter le nombre de lignes pour la hauteur
    }

    // Initialiser le vecteur tiles avec les dimensions obtenues
    tiles = vector<vector<Tile>>(fileHeight, vector<Tile>(fileWidth));
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

int Map::getFileWidth() const {
    return fileWidth;
}

int Map::getFileHeight() const {
    return fileHeight;
}

void Map::setFileWidth(int fileWidth) {
    this->fileWidth = fileWidth;
}

void Map::setFileHeight(int fileHeight) {
    this->fileHeight = fileHeight;
}

void Map::searchFileWidthHeight(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open file " << filename << endl;
        return;
    }

    string line;
    fileHeight = 0;
    while (getline(file, line)) {
        fileWidth = line.size();
        fileHeight++;
    }
    setFileHeight(fileHeight);
    setFileWidth(fileWidth);
}

void Map::createMap(const string& filename) {

    searchFileWidthHeight(filename);

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open file " << filename << endl;
        return;
    }

    string line;
    for (int x = 0; x < fileHeight; ++x) {
        getline(file, line);
        for (int y = 0; y < fileWidth; ++y) {
            // Créer une instance temporaire de Tile
            Tile tile;
            // Décoder les types de tuiles à partir du fichier
            if (line[y] == '2') {
                tile.isMonsterBegin = true;
                tile.isMonsterPath = true;
            } else if (line[y] == '3') {
                tile.isMonsterEnd = true;
                tile.isMonsterPath = true;
            } else if (line[y] == '6') {
                tile.isTurnRight = true;
                tile.isEmpty = true;
            } else if (line[y] == '7') {
                tile.isTurnLeft = true;
                tile.isEmpty = true;
            } else {
                tile.isEmpty = (line[y] == '0');
                tile.isMonsterPath = (line[y] == '1');
                tile.isTowerEmplacement = (line[y] == '4');
                tile.isDecoration = (line[y] == '5');
            }
            
            // Définir le type de tuile dans la grille
            setTileType(x, y, tile.isEmpty, tile.isMonsterPath, tile.isMonsterBegin, tile.isMonsterEnd, tile.isTowerEmplacement, tile.isDecoration, tile.isTurnRight, tile.isTurnLeft);
        }
    }
}

vector<pair<int, int>> Map::searchForWayPoints() {
    int numRows = tiles.size();
    if (numRows == 0) return wayPoints;
    int numCols = tiles[0].size();

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (tiles[i][j].isMonsterPath || tiles[i][j].isMonsterEnd) {
                wayPoints.emplace_back(j, i);
            }
        }
    }
    return wayPoints;
}