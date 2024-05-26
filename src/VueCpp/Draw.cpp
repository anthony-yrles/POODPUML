#include ".\VueH\Draw.h"

Draw::Draw(SDL_Renderer* renderer, bool clicked) {
    this->renderer = renderer;
    this->clicked = clicked;
}

void Draw::drawRect(int x, int y, int width, int height , int r, int g, int b, int a) {

    // Clamp the values, so they are between 0 and 255
    Uint8 red = clamp(r, 0, 255);
    Uint8 green = clamp(g, 0, 255);
    Uint8 blue = clamp(b, 0, 255);
    Uint8 alpha = clamp(a, 0, 255);

    // Create a rectangle
    SDL_Rect rect = { x, y, width, height };
    SDL_Color color = { red, green, blue, alpha};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Draw::drawImage(int x, int y, int width, int height , const char *image) {

    // Load the image
    SDL_Texture* texture = IMG_LoadTexture(renderer, image);
    // Error loading image handling
    if (texture == NULL) {
        cout << "Error loading image" << endl;
        return;
    }

    // Create a rectangle
    SDL_Rect rect = { x, y, width, height };
    
    // Draw and Destroy the texture
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

void Draw::drawText(int x, int y, const char *text, int r, int g, int b, int a) {

    // Clamp the values, so they are between 0 and 255
    Uint8 red = clamp(r, 0, 255);
    Uint8 green = clamp(g, 0, 255);
    Uint8 blue = clamp(b, 0, 255);
    Uint8 alpha = clamp(a, 0, 255);

    // Load the font once
    TTF_Font* font = TTF_OpenFont("arial.ttf", 40);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    // Create a surface and texture and check for errors
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, {red, green, blue, alpha});
    if (surface == NULL) {
        cout << "Error creating text" << endl;
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        cout << "Error creating texture" << endl;
        SDL_FreeSurface(surface);
        return;
    }

    // Create a rectangle and draw the texture
    SDL_Rect rect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    // Destroy the surface, texture and font
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void Draw::createButton(int x, int y, int width, int height, const char *image, int mouseX, int mouseY, bool clicked, function<void()> onClick) {
    drawImage(x, y, width, height, image);

    // Create a point for the mouse click
    SDL_Point point = { mouseX, mouseY };
    SDL_Rect buttonRect = { x, y, width, height };

    // Check if the mouse is in the button and call the function
    if (SDL_PointInRect(&point, &buttonRect)) {
        // Call onClick() only if the button has not been clicked before
        if (clicked) {
            onClick();
            clicked = false;
            cout << "Button clicked" << endl;
        }
    }
}

