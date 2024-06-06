#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Tile {
    bool isMonsterPath;
    bool isMonsterBegin;
    bool isMonsterEnd;
    bool isTowerEmplacement;

    Tile() : isMonsterPath(false), isMonsterBegin(false), isMonsterEnd(false), isTowerEmplacement(false) {}
};

class Map {
public:
    Map(int width, int height, int fileWidth, int fileHeight, const string& filename);
    ~Map();

    void setTileType(int x, int y, bool isMonsterPath, bool isMonsterBegin, bool isMonsterEnd, bool isTowerEmplacement);
    Tile getTile(int x, int y) const;
    vector<vector<Tile>> getTiles() const;
    int getWidth() const;
    int getHeight() const;
    int getFileWidth() const;
    int getFileHeight() const;
    void setFileWidth(int fileWidth);
    void setFileHeight(int fileHeight);
    void searchFileWidthHeight(const string& filename);
    void createMap(const string& filename);
    vector<pair<int, int>> searchForWayPoints();

private:
    int width;
    int height;
    int fileWidth;
    int fileHeight;
    const string filename;
    vector<vector<Tile>> tiles;
    vector<pair<int, int>> wayPoints; 
    bool wayPointFound = false;
};