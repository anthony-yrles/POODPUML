#include "./VueH/GuiHallOfFame.h"

GuiHallOfFame::GuiHallOfFame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event /*evenement*/) :
    WIDTH(WIDTH), HEIGHT(HEIGHT), mouseX(mouseX), mouseY(mouseY), clicked(clicked), running(running) {}

GuiHallOfFame::~GuiHallOfFame() {}

bool GuiHallOfFame::drawHallOfFame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement) {

    Draw draw(clicked);
    hallOfFameWindow = draw.createWindow(WIDTH, HEIGHT, "Hall of Fame", hallOfFameWindow);
    hallOfFameRenderer = draw.createRenderer(hallOfFameWindow, hallOfFameRenderer);

    draw.drawImage(hallOfFameRenderer, 0, 0, WIDTH, HEIGHT, "assets/images/hofBg.png");
    draw.drawText(hallOfFameRenderer, WIDTH / 2, 50, "Hall of Fame", 50, 50, 50, 255, 40);

    return running;
}