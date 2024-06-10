#include "./VueH/GuiInGame.h"

GuiInGame::GuiInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event /*evenement*/) {
    // Initialize member variables
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
    
    // Create game window and renderer
    gameWindow = draw.createWindow(WIDTH, HEIGHT, "Game", gameWindow);
    gameRenderer = draw.createRenderer(gameWindow, gameRenderer);
    
    // Create OptionController instance
    OptionController* optionController = new OptionController(); 

    // Create Map and MapController instances
    MapController mapController;
    const string filename = "./assets/map/map" + to_string(mapController.getLevelGame()) + ".txt";
    cout << filename << endl;
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

        // Check if options are validated
        if (!mapController.getOptionValidate()) {
            // Draw options interface
            drawOption(gameRenderer, &draw, mouseX, mouseY, clicked, &mapController, optionController);
        } else {
            // Draw game map and entities
            drawMap(filename, &map, &draw, WIDTH - 300, HEIGHT, gameRenderer, &mapController, optionController, mouseX, mouseY, clicked);
            // Spawn and move enemies if the game has started
            if (gameDebut) {
                mapController.spawnAndMoveEnemy(&map, filename, WIDTH - 300, HEIGHT, 20, 20, 5, gameRenderer, "./assets/images/gobelin.png", &draw);
            }
        }
        SDL_RenderPresent(gameRenderer);
    }
    return running;
}

void GuiInGame::drawMap(const string& filename, Map* map, Draw* draw, int width, int height, SDL_Renderer* gameRenderer, MapController* mapController, OptionController* optionController, int mouseX, int mouseY, bool clicked) {
    // Create tiles vector and initialize map
    vector<vector<Tile>> tiles = mapController->createAndReturnMap(filename, map);
    mapController->tileSize(width, height, map->getFileWidth(), map->getFileHeight());

    // Draw in-game menu
    drawMenuInGame(draw, mapController, gameRenderer, width, height, mouseX, mouseY, clicked, mapController->getLevelGame(), optionController->getDifficulty());

    // Check if victory or defeat
    if (!victory && !defeat) {
        string levelStr = to_string(mapController->getLevelGame());
        string level = levelStr + ".png";
        string fullPath = "./assets/map/map" + level;
        // Draw map background
        draw->drawImage(gameRenderer, 300, mapController->getBeginY(), width, height - mapController->getBeginY() * 2, fullPath.c_str());
        
        // Iterate through tiles
        for (size_t i = 0; i < tiles.size(); ++i) {
            for(size_t j = 0; j < tiles[i].size(); ++j) {
                if (tiles[i][j].isTowerEmplacement) {
                    bool towerPlaced = false;
                    
                    // Check if tower is placed
                    for (auto tower : mapController->getTowers()) {
                        if (tower->getEntityX() == mapController->getBeginX() + j * mapController->getTileWidth() &&
                            tower->getEntityY() == mapController->getBeginY() + i * mapController->getTileHeight()) {
                            towerPlaced = true;
                            break;
                        }
                    }

                    // Draw "+" button for tower placement
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
                    // Fire towers at enemies
                    mapController->fireTowers(mapController->getEnemies());
                }
            }
        }

        // Draw towers
        for (auto tower : mapController->getTowers()) {
            tower->drawEntity(draw);
        }
    } else if (victory) {
        // Draw victory screen
        drawVictory(gameRenderer, draw, width, height, mouseX, mouseY, clicked, mapController);
    } else if (defeat) {
        // Draw defeat screen
        drawDefeat(gameRenderer, draw, width, height, mouseX, mouseY, clicked, mapController, optionController);
    }
}

void GuiInGame::drawMenuInGame(Draw* draw, MapController* mapcontroller, SDL_Renderer* gameRenderer, int width, int height, int mouseX, int mouseY, bool clicked, int level, int difficulty) {
    // Update game attributes if not already done
    if (!attributesChanged) {
        mapcontroller->setGamesAttributes(level, difficulty);
        attributesChanged = true;
    }

    // Convert variables to strings
    string titre = "Level " + to_string(level);
    string totalEnemies = "Total enemies : " + to_string(mapcontroller->getTotalEnemiesGame());
    string enemiesLeft = "Enemies left : " + to_string(mapcontroller->getTotalEnemiesKilled());
    string gold = "Gold earned : " + to_string(mapcontroller->getGoldGames());
    string tower = "Cost : " + to_string(mapcontroller->getCostGames());
    string difficultyValue = to_string(difficulty);

    // Convert strings to const char* for drawing text
    const char* textTitre = titre.c_str();
    const char* textTotalEnemies = totalEnemies.c_str();
    const char* textEnemiesLeft = enemiesLeft.c_str();
    const char* goldEarn = gold.c_str();
    const char* towerCost = tower.c_str();
    const char* difficultyValueChar = difficultyValue.c_str();

    int lifePoints = mapcontroller->getGameLifePointsGames();

    // Draw menu elements
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
    draw->drawText(gameRenderer, 150, 335, difficultyValueChar, 0, 0, 0, 255, 25);

    // Draw life points
    for (int i = 0; i < lifePoints; i++) {
        draw->drawImage(gameRenderer, 20 + i * 25, 380, 25, 25, "./assets/images/heart.png");
    }

    // Draw begin game button
    draw->createButton(gameRenderer, 25, 490, 240, 50, "./assets/images/optionButton.png", mouseX, mouseY, clicked, [&](){
        gameDebut = true;
    });
    draw->drawText(gameRenderer, 35, 490, "Begin Game", 0, 0, 0, 255, 40);

    // Check for victory or defeat conditions
    if (mapcontroller->getTotalEnemiesKilled() == mapcontroller->getTotalEnemiesGame() && mapcontroller->getTotalEnemiesKilled() != 0){
        victory = true;
    } else if (mapcontroller->getGameLifePointsGames() == 0) {
        defeat = true;
    }
}

void GuiInGame::drawVictory(SDL_Renderer* gameRenderer, Draw* draw, int width, int height, int mouseX, int mouseY, bool clicked, MapController* mapController) {
    // Clear enemies and towers
    mapController->getEnemies().clear();
    mapController->getTowers().clear();

    // Draw victory image
    draw->drawImage(gameRenderer, width / 2, 0, width - 300, height / 3, "./assets/images/win.png");

    // Create button for next level
    draw->createButton(gameRenderer, 450, 350, 600, 100, "./assets/images/optionButton.png", mouseX, mouseY, clicked, [&](){
        // Increment level and reset flags
        mapController->setLevelGame(mapController->getLevelGame() + 1);
        victory = false;
        attributesChanged = false;
        gameDebut = false;
    });

    // Draw text for next level button
    draw->drawText(gameRenderer, 650, 370, "Next Level", 0, 0, 0, 255, 50);
}

void GuiInGame::drawDefeat(SDL_Renderer* gameRenderer, Draw* draw, int width, int height, int mouseX, int mouseY, bool clicked, MapController* mapController, OptionController* optionsController) {
    // Clear enemies and towers
    mapController->clearEnemies();
    mapController->clearTowers();

    // Draw keyboard and defeat image
    drawKeyboard(gameRenderer, draw, mouseX, mouseY, clicked, mapController, optionsController);
    draw->drawImage(gameRenderer, width / 2, 0, width - 300, height / 4, "./assets/images/lose.png");

    // Create button for retry
    draw->createButton(gameRenderer, 450, 450, 600, 100, "./assets/images/optionButton.png", mouseX, mouseY, clicked, [&](){
        // Reset level, flags, and option validation
        mapController->setLevelGame(1);
        mapController->setOptionValidate(false);
        defeat = false;
        attributesChanged = false;
        gameDebut = false;
    });

    // Draw text for retry button
    draw->drawText(gameRenderer, 700, 470, "Retry", 0, 0, 0, 255, 50);
}

// Function to draw the keyboard for entering player name
void GuiInGame::drawKeyboard(SDL_Renderer* gameRenderer, Draw* draw, int mouseX, int mouseY, bool clicked, MapController* mapController, OptionController* optionController) {
    static string name; // Static variable to hold the entered name
    draw->drawText(gameRenderer, 500, 150, "Voulez vous enregistrer votre score ?", 0, 255, 0, 255, 30); // Prompt message
    
    // Vector containing letters of the alphabet
    vector<const char*> letters = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    
    // Loop through each letter to create buttons for keyboard input
    for (int i = 0; i < 26; ++i) {
        draw->createButton(gameRenderer, 285 + i * 35, 200, 35, 35, "./assets/images/letter.png", mouseX, mouseY, clicked, [&, i]() {
            // Add the selected letter to the name if the length is less than 3, else display error message
            if (name.size() < 3) {
                name += letters[i];
            } else {
                draw->drawText(gameRenderer, 650, 300, "3 lettres maximum", 255, 0, 0, 255, 30); // Error message for exceeding max length
            }
        });
        draw->drawText(gameRenderer, 294 + i * 35, 204, letters[i], 0, 0, 0, 255, 25); // Display the letter on the button
    }
    
    // Display the entered name
    draw->drawText(gameRenderer, 610, 250, "Pseudo : ", 0, 255, 0, 255, 30);
    if (name.size() > 0) {
        draw->drawText(gameRenderer, 750, 250, name.c_str(), 0, 255, 0, 255, 30);    
    }
    
    // Button to delete the last character of the name
    draw->createButton(gameRenderer, 850, 250, 30, 30, "./assets/images/-.png", mouseX, mouseY, clicked, [&](){
        if (name.size() > 0) {
            name.pop_back();
        }
    });
    
    // Button to validate the entered name and save the score
    draw->createButton(gameRenderer, 900, 250, 30, 30, "./assets/images/validate.png", mouseX, mouseY, clicked, [&](){       
        draw->drawText(gameRenderer, 650, 300, "Score enregistre", 0, 255, 0, 255, 30); // Confirmation message
        // Write the player's name, difficulty, and game level to a file
        hofController.writeTxtFile(name.c_str(), to_string(optionController->getDifficulty()).c_str(), to_string(mapController->getLevelGame()).c_str());
    });
}

// Function to draw the options menu
void GuiInGame::drawOption(SDL_Renderer* gameRenderer, Draw* draw, int mouseX, int mouseY, bool clicked, MapController* mapController, OptionController* optionController) {
    // Draw the background image
    draw->drawImage(gameRenderer, 0, 0, 1200, 600, "./assets/images/bcgOption.png");

    // Prompt message for modifying difficulty
    draw->drawText(gameRenderer, 350, 100, "Voulez vous modifier la difficulte?", 255, 0, 0, 255, 30);
    
    // Display the current difficulty level
    string difficul = "Sans changement la difficulte sera de " + to_string(optionController->getDifficulty());
    const char* difficulty = difficul.c_str();
    draw->drawText(gameRenderer, 300, 200, difficulty, 255, 0, 0, 255, 30);
     
    // Vector to hold image file paths for difficulty buttons
    vector<string> links;

    // Loop through each difficulty level to create buttons for selection
    for (int i = 1; i < 10; i++) {
        int x = 80 + i * 100;

        stringstream ss;
        ss << "./assets/images/" << i << ".png";
        links.push_back(ss.str());

        // Button to set the selected difficulty level
        draw->createButton(gameRenderer, x, 300, 50, 50, links.back().c_str(), mouseX, mouseY, clicked, [&](){
            optionController->setDifficulty(i);
            // Display confirmation message for changed difficulty
            string difficulte = "Difficulte modifiee a " + to_string(i);
            const char* diff = difficulte.c_str();
            draw->drawText(gameRenderer, 450, 400, diff, 0, 255, 0, 255, 30);
        });
    }

    // Button to validate the options and proceed
    draw->createButton(gameRenderer, 500, 500, 200, 50, "./assets/images/validate.png", mouseX, mouseY, clicked, [&](){
        mapController->setOptionValidate(true); // Set option validation flag
    });
}