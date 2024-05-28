#include <windows.h>
#include ".\VueH\GuiMenu.h"
#include ".\ControllerH\Sound.h"

// Constants
const int WIDTH = 1200;
const int HEIGHT = 600;
int mouseX, mouseY = 0;
bool clicked = false;
SDL_Window* window;
SDL_Renderer* renderer;


// Main function
int main() {

    // Test and insitialisation of SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Échec de l'initialisation de la SDL: " << SDL_GetError();
        return 1;
    }

    Draw draw(clicked);
    window = draw.createWindow(WIDTH, HEIGHT, "Menu Tower Défense", window);
    renderer = draw.createRenderer(window, renderer);

    // Load a font
    TTF_Init();
    if (TTF_Init() != 0) {
        cerr << "Erreur d'initialisation de SDL_ttf: " << TTF_GetError();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("arial.ttf", 12);
    // Error handling
    if (!font) {
        cerr << "Erreur lors du chargement de la police: " << TTF_GetError();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop variables
    bool running = false;
    SDL_Event evenement;

    // Sound* sound = Sound::getInstance();
    // sound->loadMusic("menu", "menu.mp3");
    // sound->loadSound("click", "click.wav");
    // sound->playMusic("menu");

    // Main loop
    while (!running) {
        // Event handling
        while (SDL_PollEvent(&evenement) != 0) {
            if (evenement.type == SDL_QUIT) {
                running = true;
            } else if (evenement.type == SDL_MOUSEBUTTONDOWN) {
                clicked = true;
                // sound->playSound("click");
                SDL_GetMouseState(&mouseX, &mouseY);
            } else if (evenement.type == SDL_MOUSEBUTTONUP) {
                clicked = false;
            }
        }
        // Clear the renderer
        SDL_RenderClear(renderer);
        // Draw the menu
        GuiMenu menu(renderer, mouseX, mouseY, window, WIDTH, HEIGHT, clicked, running, evenement);
        running = menu.drawMenu(renderer, mouseX, mouseY, window, WIDTH, HEIGHT, clicked, running, evenement);
        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleaning fonts and SDL
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


// WinMain function for Windows
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hInstance = hInstance;
	hPrevInstance = hPrevInstance;
	lpCmdLine = lpCmdLine;
	nCmdShow = nCmdShow;
    // Call the main function
	main();
	return 0;
}