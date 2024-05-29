#pragma once
#include "./ModelH/Observable.h"
#include "./ModelH/Map.h"

class MapController : Observable {
public:
    MapController();
    ~MapController();

    std::vector<std::vector<Tile>> createAndReturnMap(const std::string& filename, int width, int height, Map* map);  // Changez 'vector' en 'std::vector<std::vector<Tile>>'
};
