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
    Map(int width, int height);
    ~Map();

    void setTileType(int x, int y, bool isEmpty, bool isMonsterPath, bool isMonsterBegin, bool isMonsterEnd, bool isTowerEmplacement, bool isDecoration, bool isTurnRight, bool isTurnLeft);
    Tile getTile(int x, int y) const;
    int getWidth() const;
    int getHeight() const;
    void createMap(const string& filename);

private:
    int width;
    int height;
    vector<vector<Tile>> tiles;
};