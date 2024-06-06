#include "./VueH/GuiInGame.h"

GuiInGame::GuiInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event /*evenement*/) {
    this->WIDTH = WIDTH;
    this->HEIGHT = HEIGHT;
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    this->clicked = clicked;
    this->running = running;
}

bool GuiInGame::drawInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement) {
    // Create a Draw object
    Draw draw(clicked);
    gameWindow = draw.createWindow(WIDTH, HEIGHT, "Game", gameWindow);
    gameRenderer = draw.createRenderer(gameWindow, gameRenderer);

    MapController mapController;
    const string filename = "./assets/map/map.txt";
    Map map(WIDTH - 300, HEIGHT, 0, 0, filename);

    // Game loop
    while (!running) {
        // Event handling
        while (SDL_PollEvent(&evenement) != 0) {
            if (evenement.type == SDL_QUIT) {
                running = true;
                return running;
            } else if (evenement.type == SDL_MOUSEBUTTONDOWN) {
                clicked = true;
                SDL_GetMouseState(&mouseX, &mouseY);
            } else if (evenement.type == SDL_MOUSEBUTTONUP) {
                clicked = false;
            }
        }
        SDL_RenderClear(gameRenderer);

        drawMap(filename, &map, &draw, WIDTH - 300, HEIGHT, gameRenderer, &mapController, mouseX, mouseY, clicked);
        
        mapController.spawnAndMoveEnemy(&map, filename, WIDTH - 300, HEIGHT, 5, 100, 1, gameRenderer, "./assets/images/gobelin.png", &draw);

        SDL_RenderPresent(gameRenderer);
    }
    return running;
}

void GuiInGame::drawMap(const string& filename, Map* map, Draw* draw, int width, int height, SDL_Renderer* gameRenderer, MapController* mapController, int mouseX, int mouseY, bool clicked) {
    
    vector<vector<Tile>> tiles = mapController->createAndReturnMap(filename, map);
    mapController->tileSize(width, height, map->getFileWidth(), map->getFileHeight());

    drawMenuInGame(draw, gameRenderer, width, height, "Game", "Total enemies: 5", "Enemies left: 5", "Gold: 0", "Cost: 250", mouseX, mouseY, clicked);

    draw->drawImage(gameRenderer, 300, mapController->getBeginY(), width, height - mapController->getBeginY() * 2, "./assets/map/map.png");

    for (size_t i = 0; i < tiles.size(); ++i) {
        for(size_t j = 0; j < tiles[i].size(); ++j) {
            if (tiles[i][j].isTowerEmplacement) {
                bool towerPlaced = false;
                
                for (auto tower : mapController->getTowers()) {
                    if (tower->getEntityX() == mapController->getBeginX() + j * mapController->getTileWidth() &&
                        tower->getEntityY() == mapController->getBeginY() + i * mapController->getTileHeight()) {
                        towerPlaced = true;
                        break;
                    }
                }

                if (!towerPlaced) {
                    draw->createButton(gameRenderer, mapController->getBeginX() + j * mapController->getTileWidth(), mapController->getBeginY() + i * mapController->getTileHeight(), mapController->getTileWidth(), mapController->getTileHeight(), "./assets/images/+.png", mouseX, mouseY, clicked, [&](){
                        mapController->spawnTower(1, 250, 1, 1, gameRenderer, mapController->getBeginX() + j * mapController->getTileWidth(), mapController->getBeginY() + i * mapController->getTileHeight(), mapController->getTileWidth(), mapController->getTileHeight(), "./assets/images/tower.png", draw);
                    });
                }
                mapController->fireTowers(mapController->getEnemies());
            }
        }
    }

    for (auto tower : mapController->getTowers()) {
        tower->drawEntity(draw);
    }
}

void GuiInGame::drawMenuInGame(Draw* draw, SDL_Renderer* gameRenderer, int width, int height, const char* textTitre, const char* textTotalEnemies, const char* textEnemiesLeft, const char* goldEarn, const char* towerCost, int mouseX, int mouseY, bool clicked) {
    draw->drawImage(gameRenderer, 0, 0, width + 300, height, "./assets/images/bcgMap.png");
    draw->drawImage(gameRenderer, 25, 35, 240, 40, "./assets/images/playButton.png");
    draw->drawText(gameRenderer, 90, 32, textTitre, 0, 0, 0, 255, 40);
    draw->drawImage(gameRenderer, 25, 100, 240, 40, "./assets/images/playButton.png");
    draw->drawText(gameRenderer, 27, 102, textTotalEnemies, 0, 0, 0, 0, 30);
    draw->drawImage(gameRenderer, 25, 150, 240, 40, "./assets/images/playButton.png");
    draw->drawText(gameRenderer, 27, 152, textEnemiesLeft, 0, 0, 0, 255, 30);
    draw->drawImage(gameRenderer, 25, 200, 240, 40, "./assets/images/playButton.png");
    draw->drawText(gameRenderer, 27, 202, goldEarn, 0, 0, 0, 255, 30);
    draw->drawImage(gameRenderer, 25, 250, 240, 60, "./assets/images/playButton.png");
    draw->drawImage(gameRenderer, 30, 255, 50, 50, "./assets/images/tower.png");
    draw->drawText(gameRenderer, 110, 263, towerCost, 0, 0, 0, 255, 30);
    draw->createButton(gameRenderer, 25, 490, 240, 50, "./assets/images/optionButton.png", mouseX, mouseY, clicked, [&](){
        cout << "Game begins" << endl;
    });
    draw->drawText(gameRenderer, 35, 490, "Begin Game", 0, 0, 0, 255, 40);
}
