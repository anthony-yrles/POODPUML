#include ".\VueH\GuiMenu.h"
#include ".\VueH\GuiOptions.h"
#include ".\VueH\GuiInGame.h"
#include ".\VueH\GuiHallOfFame.h"


GuiMenu::GuiMenu(SDL_Renderer* renderer, int mouseX, int mouseY, SDL_Window* window, int WIDTH, int HEIGHT, bool clicked, bool running, SDL_Event /*evenement*/) {
    this->renderer = renderer;
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    this->window = window;
    this->WIDTH = WIDTH;
    this->HEIGHT = HEIGHT;
    this->clicked = clicked;
    this->running = running;
}

bool GuiMenu::drawMenu(SDL_Renderer* renderer, int mouseX, int mouseY, SDL_Window* window, int WIDTH, int HEIGHT, bool clicked, bool running, SDL_Event evenement) {
    // Create a Draw object
    Draw draw(clicked);
    GuiOptions options(WIDTH, HEIGHT, mouseX, mouseY, clicked, running);
    GuiInGame game(WIDTH, HEIGHT, mouseX, mouseY, clicked, running, evenement);
    GuiHallOfFame hof(WIDTH, HEIGHT, mouseX, mouseY, clicked, running, evenement);

    // Using of the drawImage method from the Draw class to draw the background
    draw.drawImage(renderer, 0, 0, 1200, 600, "./assets/images/bcgMenu.png");

    // Using of the createButton method from the Draw class to create 3 buttons
    draw.createButton(renderer, 450, 230, 300, 50, "./assets/images/playButton.png", mouseX, mouseY, clicked, [&](){
        clicked = false; // Reset clicked state
        SDL_DestroyWindow(window);
        running = game.drawInGame(WIDTH, HEIGHT, mouseX, mouseY, clicked, running, evenement);
        return running;
    });
    draw.createButton(renderer, 450, 370, 300, 50, "./assets/images/optionButton.png", mouseX, mouseY, clicked, [&](){
        clicked = false; // Reset clicked state
        SDL_DestroyWindow(window);
        SDL_Window* optionWindow = NULL;
        SDL_Renderer* optionRenderer = NULL;
        running = options.drawOptions(WIDTH, HEIGHT, mouseX, mouseY, clicked, running, optionWindow, optionRenderer);
        return running;
    });
    draw.createButton(renderer, 450, 510, 300, 50, "./assets/images/hallOfFame.png", mouseX, mouseY, clicked, [&](){
        clicked = false; // Reset clicked state
        SDL_DestroyWindow(window);
        running = hof.drawHallOfFame(WIDTH, HEIGHT, mouseX, mouseY, clicked, running, evenement);
        return running;
    });

    // Using of the drawText method from the Draw class to draw the text of the buttons
    draw.drawText(renderer, 550, 230, "Jouer", 0, 0, 0, 0, 40);
    draw.drawText(renderer, 530, 370, "Options", 0, 0, 0, 0, 40);
    draw.drawText(renderer, 490, 510, "Hall of Fame", 0, 0, 0, 0, 40);

    return running;
}
