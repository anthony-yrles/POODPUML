#include ".\ModelH\GuiMenu.h"
#include ".\ModelH\GuiOptions.h"


GuiMenu::GuiMenu(SDL_Renderer* renderer, int mouseX, int mouseY, SDL_Window* window, int WIDTH, int HEIGHT, bool clicked, bool running, SDL_Event evenement) {
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
    Draw draw(renderer, clicked);
    GuiOptions options(WIDTH, HEIGHT, mouseX, mouseY, clicked, running, evenement);

    // Using of the drawImage method from the Draw class to draw the background
    draw.drawImage(0, 0, 1200, 600, "./assets/images/bcgMenu.png");

    //  Using of the creteButton method from the Draw class to create 3 buttons
    draw.createButton(450, 230, 300, 50, "./assets/images/playButton.png", mouseX, mouseY, clicked, [](){
        cout << "Button clicked" << endl;
    });
    draw.createButton(450, 370, 300, 50, "./assets/images/optionButton.png", mouseX, mouseY, clicked, [&](){
        SDL_DestroyWindow(window);
        running = options.drawOptions(WIDTH, HEIGHT, mouseX, mouseY, clicked, running, evenement);
        return running;
    });
    draw.createButton(450, 510, 300, 50, "./assets/images/hallOfFame.png", mouseX, mouseY, clicked, [](){
        cout << "Button clicked" << endl;
    });

    // Using of the drawText method from the Draw class to draw the text of the buttons
    draw.drawText(550, 230, "Jouer", 0, 0, 0, 0);
    draw.drawText(530, 370, "Options", 0, 0, 0, 0);
    draw.drawText(490, 510, "Hall of Fame", 0, 0, 0, 0);

    return running;
}