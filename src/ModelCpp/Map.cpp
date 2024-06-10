#include "./ModelH/Map.h"

// Constructor: Initializes the map with given dimensions and loads map data from file
Map::Map(int width, int height, int fileWidth, int fileHeight, const string& filename)
    : width(width), height(height), fileWidth(fileWidth), fileHeight(fileHeight) {
    
    // Open the map file
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open file " << filename << endl;
        return;
    }

    // Determine the dimensions of the map file
    string line;
    while (getline(file, line)) {
        fileWidth = line.size(); // Width is the size of the line
        fileHeight++; // Count number of lines for height
    }

    // Initialize the tiles vector with the obtained dimensions
    tiles = vector<vector<Tile>>(fileHeight, vector<Tile>(fileWidth));
}

// Destructor
Map::~Map() {}

// Set the type of tile at the given coordinates
void Map::setTileType(int x, int y, bool isMonsterPath, bool isMonsterBegin, bool isMonsterEnd, bool isTowerEmplacement) {
    tiles[x][y].isMonsterPath = isMonsterPath;
    tiles[x][y].isMonsterBegin = isMonsterBegin;
    tiles[x][y].isMonsterEnd = isMonsterEnd;
    tiles[x][y].isTowerEmplacement = isTowerEmplacement;
}

// Get the tile at the given coordinates
Tile Map::getTile(int x, int y) const {
    return tiles[x][y];
}

// Get all tiles
vector<vector<Tile>> Map::getTiles() const {
    return tiles;
}

// Get width of the map
int Map::getWidth() const {
    return width;
}

// Get height of the map
int Map::getHeight() const {
    return height;
}

// Get width of the file representing the map
int Map::getFileWidth() const {
    return fileWidth;
}

// Get height of the file representing the map
int Map::getFileHeight() const {
    return fileHeight;
}

// Set width of the file representing the map
void Map::setFileWidth(int fileWidth) {
    this->fileWidth = fileWidth;
}

// Set height of the file representing the map
void Map::setFileHeight(int fileHeight) {
    this->fileHeight = fileHeight;
}

// Search and set width and height of the file representing the map
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

// Create the map by loading data from the file
void Map::createMap(const string& filename) {
    // Search and set file width and height
    searchFileWidthHeight(filename);

    // Open the map file
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
            
            // Set tile properties based on character in the file
            tile.isMonsterPath = (line[y] == '1');
            tile.isMonsterBegin = (line[y] == '2');
            tile.isMonsterEnd = (line[y] == '3');
            tile.isTowerEmplacement = (line[y] == '4');
            
            setTileType(x, y, tile.isMonsterPath, tile.isMonsterBegin, tile.isMonsterEnd, tile.isTowerEmplacement);
        }
    }
}

// Search for waypoints in the map
vector<pair<int, int>> Map::searchForWayPoints() {
    int numRows = tiles.size();
    if (numRows == 0) return wayPoints;
    int numCols = tiles[0].size();

    if (!wayPointFound) {
        // Find the starting point
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
            // No starting point found
            return wayPoints;
        }

        // Use a queue for breadth-first search (BFS)
        queue<pair<int, int>> q;
        q.emplace(startY, startX);
        vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
        visited[startY][startX] = true;

        // Directions for up, down, left, right movements
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            wayPoints.emplace_back(y, x);

            // Traverse adjacent tiles
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
