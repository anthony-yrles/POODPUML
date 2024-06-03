#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Tile {
    bool isEmpty;
    bool isMonsterPath;
    bool isMonsterBegin;
    bool isMonsterEnd;
    bool isTowerEmplacement;
    bool isDecoration;
    bool isTurnRight;
    bool isTurnLeft;

    Tile() : isEmpty(false), isMonsterPath(false), isMonsterBegin(false), isMonsterEnd(false), isTowerEmplacement(false), isDecoration(false), isTurnRight(false), isTurnLeft(false) {}
};

class Map {
public:
    Map(int width, int height, int fileWidth, int fileHeight, const string& filename);
    ~Map();

    void setTileType(int x, int y, bool isEmpty, bool isMonsterPath, bool isMonsterBegin, bool isMonsterEnd, bool isTowerEmplacement, bool isDecoration, bool isTurnRight, bool isTurnLeft);
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
    void searchForWayPoints();

private:
    int width;
    int height;
    int fileWidth;
    int fileHeight;
    const string filename;
    vector<vector<Tile>> tiles;
    vector<pair<int, int>> wayPoints; 
};