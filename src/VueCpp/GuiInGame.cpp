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
        if (gameDebut) {
            mapController.spawnAndMoveEnemy(&map, filename, WIDTH - 300, HEIGHT, 100, 1, gameRenderer, "./assets/images/gobelin.png", &draw);
        }

        SDL_RenderPresent(gameRenderer);
    }
    return running;
}

void GuiInGame::drawMap(const string& filename, Map* map, Draw* draw, int width, int height, SDL_Renderer* gameRenderer, MapController* mapController, int mouseX, int mouseY, bool clicked) {
    
    vector<vector<Tile>> tiles = mapController->createAndReturnMap(filename, map);
    mapController->tileSize(width, height, map->getFileWidth(), map->getFileHeight());

    drawMenuInGame(draw, mapController, gameRenderer, width, height, mouseX, mouseY, clicked, 1, 9);

    if (!victory && !defeat) {
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
                            if (mapController->getGoldGames() >= mapController->getCostGames()) {
                                mapController->setGoldGames(mapController->getGoldGames() - mapController->getCostGames());
                                mapController->spawnTower(1, 250, 1, 1, gameRenderer, mapController->getBeginX() + j * mapController->getTileWidth(), mapController->getBeginY() + i * mapController->getTileHeight(), mapController->getTileWidth(), mapController->getTileHeight(), "./assets/images/tower.png", draw);
                            } else {
                                draw->drawText(gameRenderer, 50, 420, "Not enough gold", 255, 0, 0, 255, 25);
                            }
                        });
                    }
                    mapController->fireTowers(mapController->getEnemies());
                }
            }
        }

        for (auto tower : mapController->getTowers()) {
            tower->drawEntity(draw);
        }
        
    } else if (victory) {
        drawVictory(gameRenderer, draw, width, height);
    } else if (defeat) {
        drawDefeat(gameRenderer, draw, width, height);
    }
}

void GuiInGame::drawMenuInGame(Draw* draw, MapController* mapcontroller, SDL_Renderer* gameRenderer, int width, int height, int mouseX, int mouseY, bool clicked, int level, int difficulty) {

    if (!attributesChanged) {
        mapcontroller->setGamesAttributes(level, difficulty);
        attributesChanged = true;
    }

    string titre = "Level " + to_string(mapcontroller->getLevelGame() +1);
    const char* textTitre = titre.c_str();
    string totalEnemies = "Total enemies : " + to_string(mapcontroller->getTotalEnemiesGame());
    const char* textTotalEnemies = totalEnemies.c_str();
    string enemiesLeft = "Enemies left : " + to_string(mapcontroller->getTotalEnemiesKilled());
    const char* textEnemiesLeft = enemiesLeft.c_str();
    string gold = "Gold earned : " + to_string(mapcontroller->getGoldGames());
    const char* goldEarn = gold.c_str();
    string tower = "Cost : " + to_string(mapcontroller->getCostGames());
    const char* towerCost = tower.c_str();
    int lifePoints = mapcontroller->getGameLifePointsGames();

    draw->drawImage(gameRenderer, 0, 0, width + 300, height, "./assets/images/bcgMap.png");
    draw->drawImage(gameRenderer, 25, 35, 240, 40, "./assets/images/playButton.png");
    draw->drawText(gameRenderer, 90, 32, textTitre, 0, 0, 0, 255, 40);
    draw->drawImage(gameRenderer, 25, 100, 240, 40, "./assets/images/playButton.png");
    draw->drawText(gameRenderer, 27, 106, textTotalEnemies, 0, 0, 0, 0, 25);
    draw->drawImage(gameRenderer, 25, 150, 240, 40, "./assets/images/playButton.png");
    draw->drawText(gameRenderer, 27, 156, textEnemiesLeft, 0, 0, 0, 255, 25);
    draw->drawImage(gameRenderer, 25, 200, 240, 40, "./assets/images/playButton.png");
    draw->drawText(gameRenderer, 27, 206, goldEarn, 0, 0, 0, 255, 25);
    draw->drawImage(gameRenderer, 25, 250, 240, 60, "./assets/images/playButton.png");
    draw->drawImage(gameRenderer, 30, 255, 50, 50, "./assets/images/tower.png");
    draw->drawText(gameRenderer, 90, 267, towerCost, 0, 0, 0, 255, 25);
    draw->drawImage(gameRenderer, 25, 330, 240, 40, "./assets/images/playButton.png");
    draw->drawText(gameRenderer, 27, 335, "Difficulty :", 0, 0, 0, 255, 25);
    string difficultyValue = to_string(difficulty);
    const char* difficultyValueChar = difficultyValue.c_str();
    draw->drawText(gameRenderer, 150, 335, difficultyValueChar, 0, 0, 0, 255, 25);
    for (int i = 0; i < lifePoints; i++) {
        draw->drawImage(gameRenderer, 20 + i * 25, 380, 25, 25, "./assets/images/heart.png");
    }
    draw->createButton(gameRenderer, 25, 490, 240, 50, "./assets/images/optionButton.png", mouseX, mouseY, clicked, [&](){
        gameDebut = true;
    });
    draw->drawText(gameRenderer, 35, 490, "Begin Game", 0, 0, 0, 255, 40);

    if (mapcontroller->getTotalEnemiesKilled() == mapcontroller->getEnemyCreated() && mapcontroller->getTotalEnemiesKilled() != 0){
        victory = true;
    } else if (mapcontroller->getGameLifePointsGames() == 0) {
        defeat = true;
    }
}

void GuiInGame::drawVictory(SDL_Renderer* gameRenderer, Draw* draw, int width, int height) {
    draw->drawImage(gameRenderer, 0, 0, width, height, "./assets/images/win.png");
    gameDebut = false;
    attributesChanged = false;
}

void GuiInGame::drawDefeat(SDL_Renderer* gameRenderer, Draw* draw, int width, int height) {
    draw->drawImage(gameRenderer, 0, 0, width, height, "./assets/images/lose.png");
    gameDebut = false;
    attributesChanged = false;
}
