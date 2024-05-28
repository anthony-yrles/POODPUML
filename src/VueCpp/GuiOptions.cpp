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

    Draw draw(clicked);
    optionWindow = draw.createWindow(WIDTH, HEIGHT, "Options", optionWindow);
    optionRenderer = draw.createRenderer(optionWindow, optionRenderer);

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

    // Clear the renderer
    SDL_RenderClear(optionRenderer);

    // Using of the drawImage method from the Draw class to draw the background
    draw.drawImage(optionRenderer, 0, 0, 1200, 600, "./assets/images/bcgOption.png");

    draw.drawImage(optionRenderer, -100, -50, 1400, 750, "./assets/images/settings.png");

    draw.createButton(optionRenderer, 250, 180, 50, 50, "./assets/images/-.png", mouseX, mouseY, clicked, [](){
        cout << "Button clicked";
    });
    draw.createButton(optionRenderer, 1000, 180, 50, 50, "./assets/images/+.png", mouseX, mouseY, clicked, [](){
        cout << "Button clicked";
    });

    draw.drawRect(optionRenderer, 310, 180, 680, 50, 255, 255, 255, 255);
    draw.drawRect(optionRenderer, 310, 180, 680, 50, 0, 0, 0, 255);

    draw.createButton(optionRenderer, 250, 245, 50, 50, "./assets/images/-.png", mouseX, mouseY, clicked, [](){
        cout << "Button clicked";
    });
    draw.createButton(optionRenderer, 1000, 245, 50, 50, "./assets/images/+.png", mouseX, mouseY, clicked, [](){
        cout << "Button clicked";
    });

    draw.drawRect(optionRenderer, 310, 245, 680, 50, 255, 255, 255, 255);
    draw.drawRect(optionRenderer, 310, 245, 680, 50, 0, 0, 0, 255);
    
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