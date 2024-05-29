#include "./ControllerH/MapController.h"

MapController::MapController() {}

MapController::~MapController() {}

vector<vector<Tile>> MapController::createAndReturnMap(const std::string& filename, int width, int height, Map* map) {
    // Initialisez la carte avec les dimensions spécifiées
    map = new Map(width, height);
    map->createMap(filename);

    // Retournez toutes les tuiles de la carte
    return map->getTiles();
}