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
    // for (size_t i = 0; i < tiles.size(); ++i) {
    //     for (size_t j = 0; j < tiles[i].size(); ++j) {

    //         cout << "Tile at position (" << i << ", " << j << "):" << endl;
    //         cout << "isEmpty: " << tiles[i][j].isEmpty << endl;
    //         cout << "isMonsterPath: " << tiles[i][j].isMonsterPath << endl;
    //         cout << "isMonsterBegin: " << tiles[i][j].isMonsterBegin << endl;
    //         cout << "isMonsterEnd: " << tiles[i][j].isMonsterEnd << endl;
    //         cout << "isTowerEmplacement: " << tiles[i][j].isTowerEmplacement << endl;
    //         cout << "isDecoration: " << tiles[i][j].isDecoration << endl;
    //         cout << endl;
    //     }
    // }
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
    while (getline(file, line)) {
        fileWidth = line.size();
        fileHeight++;
    }
    setFileHeight(fileHeight);
    setFileWidth(fileWidth);
}

void Map::createMap(const string& filename) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open file " << filename << endl;
        return;
    }

    string line;
    for (int x = 0; x < fileHeight; ++x) {
        for (int y = 0; y < fileWidth; ++y) {
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
    }
}
