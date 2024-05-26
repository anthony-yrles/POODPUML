#include <windows.h>
#include ".\ModelH\GuiMenu.h"

// Constants
const int WIDTH = 1200;
const int HEIGHT = 600;
int mouseX, mouseY = 0;
bool clicked = false;


// Main function
int main() {

    // Test and insitialisation of SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Échec de l'initialisation de la SDL: " << SDL_GetError();
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Menu Tower Défense", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    // Error handling
    if (!window) {
        cerr << "Erreur lors de la création de la fenêtre: " << SDL_GetError();
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // Error handling
    if (!renderer) {
        cerr << "Erreur lors de la création du renderer: " << SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

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

    // Main loop
    while (!running) {
        // Event handling
        while (SDL_PollEvent(&evenement) != 0) {
            if (evenement.type == SDL_QUIT) {
                running = true;
            } else if (evenement.type == SDL_MOUSEBUTTONDOWN) {
                clicked = true;
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