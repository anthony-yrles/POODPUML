#include "./ControllerH/MapController.h"

MapController::MapController() {}

MapController::~MapController() {}

vector<vector<Tile>> MapController::createAndReturnMap(const std::string& filename, Map* map) {

    map->createMap(filename);

    // Retournez toutes les tuiles de la carte
    vector<vector<Tile>> tiles = map->getTiles();

    return tiles;
}
