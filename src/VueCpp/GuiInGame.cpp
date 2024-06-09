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
    OptionController* optionController = new OptionController(); 

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

        if(!mapController.getOptionValidate()) {
            drawOption(gameRenderer, &draw, mouseX, mouseY, clicked, &mapController, optionController);
        } else {
            drawMap(filename, &map, &draw, WIDTH - 300, HEIGHT, gameRenderer, &mapController, optionController, mouseX, mouseY, clicked);
            if (gameDebut) {
                mapController.spawnAndMoveEnemy(&map, filename, WIDTH - 300, HEIGHT, 20, 20, 5, gameRenderer, "./assets/images/gobelin.png", &draw);
            }
        }
        SDL_RenderPresent(gameRenderer);
    }
    return running;
}

void GuiInGame::drawMap(const string& filename, Map* map, Draw* draw, int width, int height, SDL_Renderer* gameRenderer, MapController* mapController, OptionController* optionController, int mouseX, int mouseY, bool clicked) {
    
    vector<vector<Tile>> tiles = mapController->createAndReturnMap(filename, map);
    mapController->tileSize(width, height, map->getFileWidth(), map->getFileHeight());

    drawMenuInGame(draw, mapController, gameRenderer, width, height, mouseX, mouseY, clicked, mapController->getLevelGame(), optionController->getDifficulty());

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
                                mapController->spawnTower(10, 250, 1, 1, gameRenderer, mapController->getBeginX() + j * mapController->getTileWidth(), mapController->getBeginY() + i * mapController->getTileHeight(), mapController->getTileWidth(), mapController->getTileHeight(), "./assets/images/tower.png", draw);
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
        drawVictory(gameRenderer, draw, width, height, mouseX, mouseY, clicked, mapController);
    } else if (defeat) {
        drawDefeat(gameRenderer, draw, width, height, mouseX, mouseY, clicked, mapController, optionController);
    }
}

void GuiInGame::drawMenuInGame(Draw* draw, MapController* mapcontroller, SDL_Renderer* gameRenderer, int width, int height, int mouseX, int mouseY, bool clicked, int level, int difficulty) {
    if (!attributesChanged) {
        mapcontroller->setGamesAttributes(level, difficulty);
        attributesChanged = true;
    }
    string titre = "Level " + to_string(level);
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

    if (mapcontroller->getTotalEnemiesKilled() == mapcontroller->getTotalEnemiesGame() && mapcontroller->getTotalEnemiesKilled() != 0){
        victory = true;
    } else if (mapcontroller->getGameLifePointsGames() == 0) {
        defeat = true;
    }
}

void GuiInGame::drawVictory(SDL_Renderer* gameRenderer, Draw* draw, int width, int height, int mouseX, int mouseY, bool clicked, MapController* mapController) {
    mapController->getEnemies().clear();
    mapController->getTowers().clear();
    draw->drawImage(gameRenderer, width / 2, 0, width - 300, height / 3, "./assets/images/win.png");
    draw->createButton(gameRenderer, 450, 350, 600, 100, "./assets/images/optionButton.png", mouseX, mouseY, clicked, [&](){
        mapController->setLevelGame(mapController->getLevelGame() + 1);
        victory = false;
        attributesChanged = false;
        gameDebut = false;
    });
    draw->drawText(gameRenderer, 650, 370, "Next Level", 0, 0, 0, 255, 50);
}

void GuiInGame::drawDefeat(SDL_Renderer* gameRenderer, Draw* draw, int width, int height, int mouseX, int mouseY, bool clicked, MapController* mapController, OptionController* optionsController) {
    mapController->clearEnemies();
    mapController->clearTowers();
    drawKeyboard(gameRenderer, draw, mouseX, mouseY, clicked, mapController, optionsController);
    draw->drawImage(gameRenderer, width / 2, 0, width - 300, height / 4, "./assets/images/lose.png");
    draw->createButton(gameRenderer, 450, 450, 600, 100, "./assets/images/optionButton.png", mouseX, mouseY, clicked, [&](){
        mapController->setLevelGame(1);
        mapController->setOptionValidate(false);
        defeat = false;
        attributesChanged = false;
        gameDebut = false;
    });
    draw->drawText(gameRenderer, 700, 470, "Retry", 0, 0, 0, 255, 50);
}

void GuiInGame::drawKeyboard(SDL_Renderer* gameRenderer, Draw* draw, int mouseX, int mouseY, bool clicked, MapController* mapController, OptionController* optionController) {
    static string name;
    draw->drawText(gameRenderer, 500, 150, "Voulez vous enregistrer votre score ?", 0, 255, 0, 255, 30);
    vector<const char*> letters = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    
    for (int i = 0; i < 26; ++i) {
        draw->createButton(gameRenderer, 285 + i * 35, 200, 35, 35, "./assets/images/letter.png", mouseX, mouseY, clicked, [&, i]() {
            if (name.size() < 3) {
                name += letters[i];
            } else {
                draw->drawText(gameRenderer, 650, 300, "3 lettres maximum", 255, 0, 0, 255, 30);
            }
        });
        draw->drawText(gameRenderer, 294 + i * 35, 204, letters[i], 0, 0, 0, 255, 25);
    }
    draw->drawText(gameRenderer, 610, 250, "Pseudo : ", 0, 255, 0, 255, 30);
    if (name.size() > 0) {
        draw->drawText(gameRenderer, 750, 250, name.c_str(), 0, 255, 0, 255, 30);    
    }
    draw->createButton(gameRenderer, 850, 250, 30, 30, "./assets/images/-.png", mouseX, mouseY, clicked, [&](){
        if (name.size() > 0) {
            name.pop_back();
        }
    });
    draw->createButton(gameRenderer, 900, 250, 30, 30, "./assets/images/validate.png", mouseX, mouseY, clicked, [&](){       
        draw->drawText(gameRenderer, 650, 300, "Score enregistre", 0, 255, 0, 255, 30);
        hofController.writeTxtFile(name.c_str(), to_string(optionController->getDifficulty()).c_str(), to_string(mapController->getLevelGame()).c_str());
    });
}

void GuiInGame::drawOption(SDL_Renderer* gameRenderer, Draw* draw, int mouseX, int mouseY, bool clicked, MapController* mapController, OptionController* optionController) {
    
    draw->drawImage(gameRenderer, 0, 0, 1200, 600, "./assets/images/bcgOption.png");

    draw->drawText(gameRenderer, 350, 100, "Voulez vous modifier la difficulte?", 255, 0, 0, 255, 30);
    string difficul = "Sans changement la difficulte sera de " + to_string(optionController->getDifficulty());
    const char* difficulty = difficul.c_str();
    draw->drawText(gameRenderer, 300, 200, difficulty, 255, 0, 0, 255, 30);
     
    vector<string> links;

    for (int i = 1; i < 10; i++) {
        int x = 80 + i * 100;

        stringstream ss;
        ss << "./assets/images/" << i << ".png";
        links.push_back(ss.str());

        draw->createButton(gameRenderer, x, 300, 50, 50, links.back().c_str(), mouseX, mouseY, clicked, [&](){
            optionController->setDifficulty(i);
            string difficulte = "Difficulte modifiee a " + to_string(i);
            const char* diff = difficulte.c_str();
            draw->drawText(gameRenderer, 450, 400, diff, 0, 255, 0, 255, 30);
        });
    }

    draw->createButton(gameRenderer, 500, 500, 200, 50, "./assets/images/validate.png", mouseX, mouseY, clicked, [&](){
        mapController->setOptionValidate(true);
    });
}