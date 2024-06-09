#include ".\VueH\GuiOptions.h"

GuiOptions::GuiOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running){
    this->WIDTH = WIDTH;
    this->HEIGHT = HEIGHT;
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    this->clicked = clicked;
    this->running = running;
}

bool GuiOptions::drawOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Window* optionWindow, SDL_Renderer* optionRenderer) {

    clicked = false;
    Draw draw(clicked);
    optionWindow = draw.createWindow(WIDTH, HEIGHT, "Options", optionWindow);
    optionRenderer = draw.createRenderer(optionWindow, optionRenderer);
    OptionController* optionController;

    // Option loop
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

    SDL_RenderClear(optionRenderer);

    draw.drawImage(optionRenderer, 0, 0, 1200, 600, "./assets/images/bcgOption.png");

    draw.drawImage(optionRenderer, -100, -50, 1400, 750, "./assets/images/settings.png");

    draw.createButton(optionRenderer, 250, 200, 50, 50, "./assets/images/-.png", mouseX, mouseY, clicked, [&optionController](){
        optionController->decreaseVolume();
        cout << optionController->getVolume() << endl;
    });
    draw.createButton(optionRenderer, 1000, 200, 50, 50, "./assets/images/+.png", mouseX, mouseY, clicked, [&optionController](){
        optionController->increaseVolume();
        cout << optionController->getVolume() << endl;
    });

    rectVolume(optionRenderer, 310, 200, 680, 50, optionController->getVolume(), 132, &draw);

    
    vector<string> links;

    for (int i = 1; i < 10; i++) {
        int x = 80 + i * 100;

        stringstream ss;
        ss << "./assets/images/" << i << ".png";
        links.push_back(ss.str());

        draw.createButton(optionRenderer, x, 400, 50, 50, links.back().c_str(), mouseX, mouseY, clicked, [&](){
            cout << "Button " + to_string(i) + " clicked";
        });
    }
    SDL_RenderPresent(optionRenderer);
    }

    // Destroy the renderer
    SDL_DestroyRenderer(optionRenderer);
    // Destroy the window
    SDL_DestroyWindow(optionWindow);
    // Quit SDL
    SDL_Quit();

    return running;
}

void GuiOptions::rectVolume(SDL_Renderer* renderer, int x, int y, int width, int height, int currentVolume, int maxVolume, Draw* draw) {

    float volumePercentage = static_cast<float>(currentVolume) / static_cast<float>(maxVolume);
    int red = static_cast<int>((1.0f - volumePercentage) * 255);
    int green = static_cast<int>(volumePercentage * 255);
    float widthPercentage = static_cast<float>(width) * volumePercentage;

    draw->drawRect(renderer, x, y, widthPercentage, height, red, green, 0, 255);
}