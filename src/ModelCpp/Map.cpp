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

void Map::setTileType(int x, int y, bool isMonsterPath, bool isMonsterBegin, bool isMonsterEnd, bool isTowerEmplacement) {
    tiles[x][y].isMonsterPath = isMonsterPath;
    tiles[x][y].isMonsterBegin = isMonsterBegin;
    tiles[x][y].isMonsterEnd = isMonsterEnd;
    tiles[x][y].isTowerEmplacement = isTowerEmplacement;
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
            Tile tile;
            
            tile.isMonsterPath = (line[y] == '1');
            tile.isMonsterBegin = (line[y] == '2');
            tile.isMonsterEnd = (line[y] == '3');
            tile.isTowerEmplacement = (line[y] == '4');
            
            setTileType(x, y, tile.isMonsterPath, tile.isMonsterBegin, tile.isMonsterEnd, tile.isTowerEmplacement);
        }
    }
}

vector<pair<int, int>> Map::searchForWayPoints() {
    int numRows = tiles.size();
    if (numRows == 0) return wayPoints;
    int numCols = tiles[0].size();

    if (!wayPointFound) {
        // Trouver le point de départ
        int startX = -1, startY = -1;
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if (tiles[i][j].isMonsterBegin) {
                    startX = j;
                    startY = i;
                    break;
                }
            }
            if (startX != -1 && startY != -1) break;
        }

        if (startX == -1 || startY == -1) {
            // Aucun point de départ trouvé
            return wayPoints;
        }

        // Utiliser une queue pour le parcours en largeur (BFS)
        queue<pair<int, int>> q;
        q.emplace(startY, startX);
        vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
        visited[startY][startX] = true;

        // Directions pour les mouvements haut, bas, gauche, droite
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            wayPoints.emplace_back(y, x);

            // Parcourir les tuiles adjacentes
            for (const auto& [dx, dy] : directions) {
                int newX = x + dx;
                int newY = y + dy;

                if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols &&
                    !visited[newX][newY] && 
                    (tiles[newX][newY].isMonsterPath || tiles[newX][newY].isMonsterEnd)) {
                    q.emplace(newX, newY);
                    visited[newX][newY] = true;
                }
            }
        }

        wayPointFound = true;
    }
    return wayPoints;
}