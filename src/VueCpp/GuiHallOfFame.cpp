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

            difficultyHof = returnDifficulty(draw, hallOfFameRenderer);

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

int GuiHallOfFame::returnDifficulty(Draw draw, SDL_Renderer* hallOfFameRenderer) {
    vector<string> links;

    draw.drawText(hallOfFameRenderer, 400, 130, "Veuillez selectionner la difficulte", 0, 0, 0, 255, 30);

    for (int i = 1; i < 10; i++) {
        int x = 80 + i * 100;

        stringstream ss;
        ss << "./assets/images/" << i << ".png";
        links.push_back(ss.str());

        draw.createButton(hallOfFameRenderer, x, 180, 50, 50, links.back().c_str(), mouseX, mouseY, clicked, [&](){
            difficultyHof = i;
            cout << "Difficulte selectionnee : " << difficultyHof << endl;
        });
    }
    return difficultyHof;
}

void GuiHallOfFame::drawData(int difficultyHof, Draw draw, SDL_Renderer* hallOfFameRenderer, HofController hofController) {
    hofController.sortDataByDifficulty(difficultyHof);

    for (long long unsigned int i = 0; i < hofController.getSortedDataFoh().size(); i++) {
        stringstream ss;
        ss << hofController.getSortedDataFoh()[i].name << " - " << hofController.getSortedDataFoh()[i].level;
        draw.drawText(hallOfFameRenderer, 400, 200 + i * 50, ss.str().c_str(), 0, 0, 0, 255, 30);
    }
}

void GuiHallOfFame::update() {
    hofController.readTxtFile();
}