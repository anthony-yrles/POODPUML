#include ".\VueH\GuiMenu.h"
#include ".\VueH\GuiOptions.h"
#include ".\ControllerH\Sound.h"


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

    CreateFromJson createFromJson;
    json jsonData = createFromJson.readJsonFile("./assets/draw.json");
    running = createFromJson.readMenu(jsonData, Draw(), renderer, mouseX, mouseY, clicked, window, running, Options(), WIDTH, HEIGHT);
    return running;
}