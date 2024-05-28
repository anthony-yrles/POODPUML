#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum class TileType {
    EMPTY,
    DECORATION,
    MONSTER_PATH,
    TOWER_EMPLACEMENT
};

struct Tile {
    TileType type;
};

class Map {
    public:
        Map(int width, int height);
        ~Map();

        void setTileType(int x, int y, TileType type);
        TileType getTileType(int x, int y);
        int getWidth();
        int getHeight();
        void createMap(string& filename);
        
    private:
        int width;
        int height;
        vector<vector<TileType>> tiles;
};