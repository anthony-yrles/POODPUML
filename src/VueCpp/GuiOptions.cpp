#include ".\VueH\GuiOptions.h"

GuiOptions::GuiOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement){
    this->WIDTH = WIDTH;
    this->HEIGHT = HEIGHT;
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    this->clicked = clicked;
    this->running = running;
}

bool GuiOptions::drawOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement) {

    // Create a new window
    SDL_Window* optionWindow = SDL_CreateWindow("Options", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    // Error handling
    if (!optionWindow) {
        cerr << "Erreur lors de la création de la fenêtre: " << SDL_GetError();
        SDL_Quit();
        return running;
    }

    // Create a renderer
    SDL_Renderer* optionRenderer = SDL_CreateRenderer(optionWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // Error handling
    if (!optionRenderer) {
        cerr << "Erreur lors de la création du renderer: " << SDL_GetError();
        SDL_DestroyWindow(optionWindow);
        SDL_Quit();
        return running;
    }

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
    // Create a Draw object
    Draw draw(optionRenderer, clicked);

    // Clear the renderer
    SDL_RenderClear(optionRenderer);

    // Using of the drawImage method from the Draw class to draw the background
    draw.drawImage(0, 0, 1200, 600, "./assets/images/bcgOption.png");

    draw.drawImage(-100, -50, 1400, 750, "./assets/images/settings.png");

    draw.createButton(250, 180, 50, 50, "./assets/images/-.png", mouseX, mouseY, clicked, [](){
        cout << "Button clicked";
    });
    draw.createButton(1000, 180, 50, 50, "./assets/images/+.png", mouseX, mouseY, clicked, [](){
        cout << "Button clicked";
    });

    draw.drawRect(310, 180, 680, 50, 255, 255, 255, 255);
    draw.drawRect(310, 180, 680, 50, 0, 0, 0, 255);

    draw.createButton(250, 245, 50, 50, "./assets/images/-.png", mouseX, mouseY, clicked, [](){
        cout << "Button clicked";
    });
    draw.createButton(1000, 245, 50, 50, "./assets/images/+.png", mouseX, mouseY, clicked, [](){
        cout << "Button clicked";
    });

    draw.drawRect(310, 245, 680, 50, 255, 255, 255, 255);
    draw.drawRect(310, 245, 680, 50, 0, 0, 0, 255);
    
    vector<string> links;

    for (int i = 1; i < 10; i++) {
        int x = 80 + i * 100;

        stringstream ss;
        ss << "./assets/images/" << i << ".png";
        links.push_back(ss.str());

        draw.createButton(x, 400, 50, 50, links.back().c_str(), mouseX, mouseY, clicked, [&](){
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