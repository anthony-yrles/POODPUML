#ifndef CREATEFROMJSON_H
#define CREATEFROMJSON_H

#include "./VueH/Draw.h"
#include <SDL2/nlohmann/json.hpp>
#include <fstream>
#include <unordered_map>

using json = nlohmann::json;

class CreateFromJson {
    
    // The CreateFromJson class is responsible for reading the json file and drawing the menu on the screen

public:
    explicit CreateFromJson(int mouseX, int mouseY, bool clicked);
    json readJsonFile(ifstream& file);
    bool readMenu(const json& jsonData, Draw& draw, SDL_Renderer* renderer, int mouseX, int mouseY, bool clicked, SDL_Window* window, bool running, Options& options, int WIDTH, int HEIGHT);
    void readOptions(const json& jsonData, Draw& draw, SDL_Renderer* renderer, int mouseX, int mouseY);

private:
    int mouseX;
    int mouseY;
    bool clicked;
};

#endif // CREATEFROMJSON_H