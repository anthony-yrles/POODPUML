#pragma once
#include "./ModelH/Observable.h"
#include "./ModelH/Map.h"

class MapController : Observable {
public:
    MapController();
    ~MapController();

    vector<vector<Tile>> createAndReturnMap(const std::string& filename, Map* map);
};
