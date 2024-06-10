#include ".\VueH\GuiOptions.h"

// Constructor
GuiOptions::GuiOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running) {
    this->WIDTH = WIDTH;
    this->HEIGHT = HEIGHT;
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    this->clicked = clicked;
    this->running = running;
}

// Method to draw the options interface
bool GuiOptions::drawOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Window* optionWindow, SDL_Renderer* optionRenderer) {
    clicked = false; // Reset clicked flag
    Draw draw(clicked); // Create Draw object with click status
    optionWindow = draw.createWindow(WIDTH, HEIGHT, "Options", optionWindow); // Create SDL window
    optionRenderer = draw.createRenderer(optionWindow, optionRenderer); // Create SDL renderer
    OptionController* optionController = new OptionController(); // Create OptionController object

    // Option loop
    while (!running) {
        // Event handling
        while (SDL_PollEvent(&evenement) != 0) {
            if (evenement.type == SDL_QUIT) {
                running = true; // Quit loop if quit event is triggered
                return running;
            } else if (evenement.type == SDL_MOUSEBUTTONDOWN) {
                clicked = true; // Set clicked flag to true when mouse button is pressed
                SDL_GetMouseState(&mouseX, &mouseY); // Get mouse position
            } else if (evenement.type == SDL_MOUSEBUTTONUP) {
                clicked = false; // Set clicked flag to false when mouse button is released
            }
        }

        SDL_RenderClear(optionRenderer); // Clear the renderer

        // Draw background and settings image
        draw.drawImage(optionRenderer, 0, 0, 1200, 600, "./assets/images/bcgOption.png");
        draw.drawImage(optionRenderer, -100, -50, 1400, 750, "./assets/images/settings.png");

        // Create volume control buttons and rectangle
        draw.createButton(optionRenderer, 250, 200, 50, 50, "./assets/images/-.png", mouseX, mouseY, clicked, [&optionController](){
            optionController->decreaseVolume(); // Decrease volume when "-" button is clicked
        });
        draw.createButton(optionRenderer, 1000, 200, 50, 50, "./assets/images/+.png", mouseX, mouseY, clicked, [&optionController](){
            optionController->increaseVolume(); // Increase volume when "+" button is clicked
        });
        rectVolume(optionRenderer, 310, 200, 680, 50, optionController->getVolume(), 132, &draw); // Draw volume control rectangle

        // Handle difficulty selection
        difficultyChoice(draw, optionRenderer, optionController, mouseX, mouseY, clicked);

        // Validate button
        draw.createButton(optionRenderer, 965, 480, 65, 65, "./assets/images/validate.png", mouseX, mouseY, clicked, [&running](){
            cout << "Options validées" << endl; // Log message when validate button is clicked
        });

        SDL_RenderPresent(optionRenderer); // Update the renderer
    }

    // Destroy the renderer
    SDL_DestroyRenderer(optionRenderer);
    // Destroy the window
    SDL_DestroyWindow(optionWindow);
    // Quit SDL
    SDL_Quit();

    return running;
}

// Method to draw the volume control rectangle
void GuiOptions::rectVolume(SDL_Renderer* renderer, int x, int y, int width, int height, int currentVolume, int maxVolume, Draw* draw) {
    // Calculate volume percentage and color
    float volumePercentage = static_cast<float>(currentVolume) / static_cast<float>(maxVolume);
    int red = static_cast<int>((1.0f - volumePercentage) * 255);
    int green = static_cast<int>(volumePercentage * 255);
    float widthPercentage = static_cast<float>(width) * volumePercentage;

    // Draw volume control rectangle
    draw->drawRect(renderer, x, y, widthPercentage, height, red, green, 0, 255);
}

void GuiOptions::difficultyChoice(Draw draw, SDL_Renderer* optionRenderer, OptionController* optionController, int mouseX, int mouseY, bool clicked) {
    vector<string> links;

    // Create buttons for each difficulty level
    for (int i = 1; i < 10; i++) {
        int x = 80 + i * 100;

        stringstream ss;
        ss << "./assets/images/" << i << ".png";
        links.push_back(ss.str());

        // Create button for each difficulty level
        draw.createButton(optionRenderer, x, 400, 50, 50, links.back().c_str(), mouseX, mouseY, clicked, [&](){
            cout << "Difficulty chosen: " << i << endl; // Log the chosen difficulty
            optionController->setDifficulty(i); // Set the difficulty level
        });
    }

    // Display the chosen difficulty if it's not the default value
    if (optionController->getDifficulty() != 0) {
        string difficultyString = "Difficulty chosen: " + to_string(optionController->getDifficulty());
        const char* difficultyChoosed = difficultyString.c_str();
        draw.drawText(optionRenderer, 400, 130, difficultyChoosed, 0, 0, 0, 255, 30);
    }
}