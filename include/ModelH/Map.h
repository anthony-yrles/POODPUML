#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

/**
 * @struct Tile
 * @brief Represents a tile on the map.
 *
 * The Tile structure holds boolean values indicating if a tile is part of the monster path,
 * the beginning of the path, the end of the path, or a tower emplacement.
 */
struct Tile {
    bool isMonsterPath;      ///< Indicates if the tile is part of the monster path.
    bool isMonsterBegin;     ///< Indicates if the tile is the beginning of the monster path.
    bool isMonsterEnd;       ///< Indicates if the tile is the end of the monster path.
    bool isTowerEmplacement; ///< Indicates if the tile is a tower emplacement.

    /**
     * @brief Constructs a Tile with default values.
     */
    Tile() : isMonsterPath(false), isMonsterBegin(false), isMonsterEnd(false), isTowerEmplacement(false) {}
};

/**
 * @class Map
 * @brief Manages the game's map.
 *
 * The Map class provides functionalities to initialize and manipulate the map,
 * set tile types, and search for waypoints.
 */
class Map {
public:
    /**
     * @brief Constructs a Map object.
     * @param width Width of the map.
     * @param height Height of the map.
     * @param fileWidth Width of the map file.
     * @param fileHeight Height of the map file.
     * @param filename Name of the map file.
     */
    Map(int width, int height, int fileWidth, int fileHeight, const string& filename);

    /**
     * @brief Destructor for the Map class.
     */
    ~Map();

    /**
     * @brief Sets the type of a tile.
     * @param x X-coordinate of the tile.
     * @param y Y-coordinate of the tile.
     * @param isMonsterPath Whether the tile is part of the monster path.
     * @param isMonsterBegin Whether the tile is the beginning of the monster path.
     * @param isMonsterEnd Whether the tile is the end of the monster path.
     * @param isTowerEmplacement Whether the tile is a tower emplacement.
     */
    void setTileType(int x, int y, bool isMonsterPath, bool isMonsterBegin, bool isMonsterEnd, bool isTowerEmplacement);

    /**
     * @brief Gets a tile at a specific position.
     * @param x X-coordinate of the tile.
     * @param y Y-coordinate of the tile.
     * @return The tile at the specified position.
     */
    Tile getTile(int x, int y) const;

    /**
     * @brief Gets all tiles in the map.
     * @return A vector of vectors containing all tiles.
     */
    vector<vector<Tile>> getTiles() const;

    /**
     * @brief Gets the width of the map.
     * @return The width of the map.
     */
    int getWidth() const;

    /**
     * @brief Gets the height of the map.
     * @return The height of the map.
     */
    int getHeight() const;

    /**
     * @brief Gets the width of the map file.
     * @return The width of the map file.
     */
    int getFileWidth() const;

    /**
     * @brief Gets the height of the map file.
     * @return The height of the map file.
     */
    int getFileHeight() const;

    /**
     * @brief Sets the width of the map file.
     * @param fileWidth The width of the map file.
     */
    void setFileWidth(int fileWidth);

    /**
     * @brief Sets the height of the map file.
     * @param fileHeight The height of the map file.
     */
    void setFileHeight(int fileHeight);

    /**
     * @brief Determines the dimensions of the map file.
     * @param filename Name of the map file.
     */
    void searchFileWidthHeight(const string& filename);

    /**
     * @brief Creates the map from a file.
     * @param filename Name of the map file.
     */
    void createMap(const string& filename);

    /**
     * @brief Searches for waypoints in the map.
     * @return A vector of pairs representing the waypoints.
     */
    vector<pair<int, int>> searchForWayPoints();

private:
    int width;                ///< Width of the map.
    int height;               ///< Height of the map.
    int fileWidth;            ///< Width of the map file.
    int fileHeight;           ///< Height of the map file.
    const string filename;    ///< Name of the map file.
    vector<vector<Tile>> tiles; ///< 2D vector of tiles.
    vector<pair<int, int>> wayPoints; ///< Vector of waypoints.
    bool wayPointFound = false; ///< Flag indicating if waypoints have been found.
};