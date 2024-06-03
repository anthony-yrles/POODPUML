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
    
    drawEnemy(&map, &mapController, &draw, filename, 10, WIDTH - 300, HEIGHT, gameRenderer);

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
        drawMap(filename, &map, &draw, WIDTH - 300, HEIGHT, gameRenderer, &mapController);
        if (enemiesDrawn.size() > 0) {
            for (auto enemy : enemiesDrawn) {
                enemy->drawEntity(&draw);
            }
        }
        SDL_RenderPresent(gameRenderer);
    }
    return running;
}

void GuiInGame::tileSize(int WIDTH, int HEIGHT, int filewidth, int fileheight) {
    if (filewidth > fileheight) {
        tileWidth = WIDTH / filewidth;
        tileHeight = tileWidth;
        beginY = (HEIGHT - (tileHeight * fileheight)) / 2;
    } else {
        tileHeight = HEIGHT / fileheight;
        tileWidth = tileHeight;
        beginX = (WIDTH - (tileWidth * filewidth)) / 2;
    }
}

void GuiInGame::drawMap(const string& filename, Map* map, Draw* draw, int width, int height, SDL_Renderer* gameRenderer, MapController* mapController) {
    
    vector<vector<Tile>> tiles = mapController->createAndReturnMap(filename, map);
    tileSize(width, height, map->getFileWidth(), map->getFileHeight());

    for (long long unsigned int i = 0; i < tiles.size(); ++i) {
        for (long long unsigned int j = 0; j < tiles[i].size(); ++j) {
            if (tiles[i][j].isEmpty) {
                draw->drawRect(gameRenderer, beginX + j * tileWidth, beginY + i * tileHeight, tileWidth, tileHeight, 0, 255, 0, 255);
            } else if (tiles[i][j].isMonsterBegin) {
                draw->drawRect(gameRenderer, beginX + j * tileWidth, beginY + i * tileHeight, tileWidth, tileHeight, 255, 0, 0, 255);
            } else if (tiles[i][j].isMonsterEnd) {
                draw->drawRect(gameRenderer, beginX + j * tileWidth, beginY + i * tileHeight, tileWidth, tileHeight, 255, 0, 0, 255);
            } else if (tiles[i][j].isMonsterPath) {
                draw->drawRect(gameRenderer, beginX + j * tileWidth, beginY + i * tileHeight, tileWidth, tileHeight, 255, 0, 255, 255);
            } else if (tiles[i][j].isTowerEmplacement) {
                draw->drawRect(gameRenderer, beginX + j * tileWidth, beginY + i * tileHeight, tileWidth, tileHeight, 0, 0, 255, 255);
            } else if (tiles[i][j].isDecoration) {
                draw->drawRect(gameRenderer, beginX + j * tileWidth, beginY + i * tileHeight, tileWidth, tileHeight, 255, 255, 0, 255);
            }
        }
    }
}

void GuiInGame::drawEnemy(Map* map, MapController* mapController, Draw* draw, const string& filename, int enemyNumber, int width, int height, SDL_Renderer* gameRenderer) {

    vector<vector<Tile>> tiles = mapController->createAndReturnMap(filename, map);
    tileSize(width, height, map->getFileWidth(), map->getFileHeight());

    mapController->createEnemy(100, 1, enemyNumber, gameRenderer, beginX, beginY, tileWidth, tileHeight, "./assets/images/gobelin.png");

    if (mapController->spawnTime()) {
        for (size_t i = 0; i < tiles.size() && enemySpawned <= enemyNumber; ++i) {
            for (size_t j = 0; j < tiles[i].size() && enemySpawned <= enemyNumber; ++j) {
                if (tiles[i][j].isMonsterBegin) {
                    auto enemy = mapController->getEnemy(enemySpawned); 
                    enemy->setEntityX(beginX + j * tileWidth);
                    enemy->setEntityY(beginY + i * tileHeight);
                    enemy->setEntityWidth(tileWidth);
                    enemy->setEntityHeight(tileHeight);
                    enemiesDrawn.push_back(enemy);
                    enemy->drawEntity(draw);
                    ++enemySpawned;
                }
            }
        }
    }
}
