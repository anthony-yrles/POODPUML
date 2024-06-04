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
    
    // drawEnemy(&map, &mapController, &draw, filename, 1, WIDTH - 300, HEIGHT, gameRenderer);

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
        // SDL_RenderClear(gameRenderer);

        drawMap(filename, &map, &draw, WIDTH - 300, HEIGHT, gameRenderer, &mapController);
        
        drawEnemy(&map, &mapController, &draw, filename, 10, WIDTH - 300, HEIGHT, gameRenderer);

        mapController.moveEnemies(enemiesDrawn, mapController.searchForWayPoints(&map), &draw);
        
        SDL_RenderPresent(gameRenderer);
    }
    return running;
}

void GuiInGame::drawMap(const string& filename, Map* map, Draw* draw, int width, int height, SDL_Renderer* gameRenderer, MapController* mapController) {
    
    vector<vector<Tile>> tiles = mapController->createAndReturnMap(filename, map);
    mapController->tileSize(width, height, map->getFileWidth(), map->getFileHeight());

    draw->drawImage(gameRenderer, 300, mapController->getBeginY(), width, height - mapController->getBeginY() * 2, "./assets/map/map.png");
}

void GuiInGame::drawEnemy(Map* map, MapController* mapController, Draw* draw, const string& filename, int enemyNumber, int width, int height, SDL_Renderer* gameRenderer) {
    // Assurez-vous que les ennemis sont créés une seule fois
    mapController->createEnemy(100, 3, enemyNumber, gameRenderer, 0, 0, 0, 0, "./assets/images/gobelin.png");

    // Positionnez les ennemis
    mapController->setEnemiesPositions(map, filename, enemyNumber, width, height);

    // Dessinez les ennemis
    if (enemySpawned < enemyNumber) {
        for (int k = 0; k < enemyNumber; ++k) {
            if (mapController->spawnTime()) {
                auto enemy = mapController->getEnemy(k);
                if (enemy) {
                    enemiesDrawn.push_back(enemy);
                    enemy->drawEntity(draw);
                }
                enemySpawned++;
            }
        }
    }
}