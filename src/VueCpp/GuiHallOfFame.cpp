#include "./VueH/GuiHallOfFame.h"

GuiHallOfFame::GuiHallOfFame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event /*evenement*/) :
    WIDTH(WIDTH), HEIGHT(HEIGHT), mouseX(mouseX), mouseY(mouseY), clicked(clicked), running(running) {
        hofController.addObserver(this);
    }

GuiHallOfFame::~GuiHallOfFame() {
    hofController.removeObserver(this);
}

bool GuiHallOfFame::drawHallOfFame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement) {

    Draw draw(clicked);
    hallOfFameWindow = draw.createWindow(WIDTH, HEIGHT, "Hall of Fame", hallOfFameWindow);
    hallOfFameRenderer = draw.createRenderer(hallOfFameWindow, hallOfFameRenderer);
    hofController.readTxtFile();

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
            SDL_RenderClear(hallOfFameRenderer);

            draw.drawImage(hallOfFameRenderer, 0, 0, WIDTH, HEIGHT, "assets/images/hofBg.png");
            draw.drawText(hallOfFameRenderer, 500, 60, "Hall of Fame", 50, 50, 50, 255, 40);
            draw.drawImage(hallOfFameRenderer, 200, 300, 800, 250, "assets/images/podium.png");

            difficultyHof = returnDifficulty(draw, hallOfFameRenderer, mouseX, mouseY, clicked);

            drawData(difficultyHof, draw, hallOfFameRenderer, hofController);

            SDL_RenderPresent(hallOfFameRenderer);
        }
    }
    // Destroy the renderer
    SDL_DestroyRenderer(hallOfFameRenderer);
    // Destroy the window
    SDL_DestroyWindow(hallOfFameWindow);
    // Quit SDL
    SDL_Quit();
    return running;
}

int GuiHallOfFame::returnDifficulty(Draw draw, SDL_Renderer* hallOfFameRenderer, int mouseX, int mouseY, bool clicked) {
    vector<string> links;

    draw.drawText(hallOfFameRenderer, 400, 130, "Veuillez selectionner la difficulte", 0, 0, 0, 255, 30);

    for (int i = 1; i < 10; i++) {
        int x = 80 + i * 100;
        stringstream ss;
        ss << "./assets/images/" << i << ".png";
        links.push_back(ss.str());

        draw.createButton(hallOfFameRenderer, x, 180, 50, 50, links.back().c_str(), mouseX, mouseY, clicked, [&](){
            cout << "Difficulte choisie : " << i << endl;
            difficultyHof = i;
        });
    }
    return difficultyHof;
}

void GuiHallOfFame::drawData(int difficultyHof, Draw draw, SDL_Renderer* hallOfFameRenderer, HofController hofController) {
    hofController.topThreeSortedData(difficultyHof);


    for (long long unsigned int i = 0; i < hofController.getSortedDataFoh().size(); i++) {
        stringstream ss;
        ss << hofController.getSortedDataFoh()[i].name << " - " << hofController.getSortedDataFoh()[i].level;
        if (i == 0) {
            draw.drawImage(hallOfFameRenderer, 500, 240, 200, 40, "assets/images/hallOfFame.png");
            draw.drawText(hallOfFameRenderer, 550, 243, ss.str().c_str(), 255, 215, 0, 255, 30);
        } else if (i == 1) {
            draw.drawImage(hallOfFameRenderer, 250, 270, 200, 40, "assets/images/hallOfFame.png");
            draw.drawText(hallOfFameRenderer, 300, 273, ss.str().c_str(), 192, 192, 192, 255, 30);
        } else if (i == 2) {
            draw.drawImage(hallOfFameRenderer, 750, 300, 200, 40, "assets/images/hallOfFame.png");
            draw.drawText(hallOfFameRenderer, 800, 303, ss.str().c_str(), 205, 127, 50, 255, 30);
        }
    }
}

void GuiHallOfFame::update() {
    hofController.readTxtFile();
}