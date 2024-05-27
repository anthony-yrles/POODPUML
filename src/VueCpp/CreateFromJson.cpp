#include "./VueH/CreateFromJson.h"

CreateFromJson::CreateFromJson(int mouseX, int mouseY, bool clicked) {
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    this->clicked = clicked;
}
    
json CreateFromJson::readJsonFile(ifstream& file) {

    // Handle the json
    file.open("./VueCpp/draw.json");
    if (!file.is_open()) {
        cout << "Error opening file";
        return;
    }
    // Read the json
    json jsonData;
    try {
        file >> jsonData;
    } catch (const std::exception &e) {
        cerr << "Erreur lors de la lecture du fichier JSON : " << e.what();
        return json();
    }

    // Close the file
    file.close();
    return jsonData;
}

bool CreateFromJson::readMenu(const json& jsonData, Draw& draw, SDL_Renderer* renderer, int mouseX, int mouseY, bool clicked, SDL_Window* window, bool running, Options& options, int WIDTH, int HEIGHT) {

    unordered_map<string, function<void()>> actionMap = {
        {"playAction", []() { std::cout << "Play button clicked"; }},
        {"optionsAction", [&]() {
            SDL_DestroyWindow(window);
            running = options.drawOptions(WIDTH, HEIGHT, mouseX, mouseY, clicked, running)
            return running;
        }},
        {"hallOfFameAction", []() { std::cout << "Hall of Fame button clicked"; }}
    };

    if (jsonData.contains("menu") && jsonData["menu"].contains("image")) {
        for (const auto& item : jsonData["menu"]["image"]) {
            int x = item["x"].get<int>();
            int y = item["y"].get<int>();
            int width = item["width"].get<int>();
            int height = item["height"].get<int>();
            string imagePath = item["imagePath"].get<string>();

            draw.drawImage(renderer, x, y, width, height, imagePath.c_str());
        }
    } else if (jsonData.contains("menu") && jsonData["menu"].contains("text")) {
        for (const auto& item : jsonData["menu"]["text"]) {
            int x = item["x"].get<int>();
            int y = item["y"].get<int>();
            string text = item["text"].get<string>();
            int r = item["r"].get<int>();
            int g = item["g"].get<int>();
            int b = item["b"].get<int>();
            int a = item["a"].get<int>();

            draw.drawText(renderer, x, y, text.c_str(), r, g, b, a);
        }
    } else if (jsonData.contains("menu") && jsonData["menu"].contains("buttons")) {
        for (const auto& item : jsonData["menu"]["button"]) {
            int x = item["x"].get<int>();
            int y = item["y"].get<int>();
            int width = item["width"].get<int>();
            int height = item["height"].get<int>();
            string imagePath = item["imagePath"].get<string>();
            string method = item["method"].get<string>();

            draw.createButton(renderer, x, y, width, height, imagePath.c_str(), mouseX, mouseY, clicked, actionMap[method]);
        }
    } else if (jsonData.contains("menu") && jsonData["menu"].contains("rect")) {
        for (const auto& item : jsonData["menu"]["rectangle"]) {
            int x = item["x"].get<int>();
            int y = item["y"].get<int>();
            int width = item["width"].get<int>();
            int height = item["height"].get<int>();
            int r = item["r"].get<int>();
            int g = item["g"].get<int>();
            int b = item["b"].get<int>();
            int a = item["a"].get<int>();

            draw.drawRect(renderer, x, y, width, height, r, g, b, a);
        }
    }
}

void CreateFromJson::readOptions(const json& jsonData, Draw& draw, SDL_Renderer* renderer, int mouseX, int mouseY) {
    unordered_map<string, function<void()>> actionMap = {
        {"buttonLessMusicAction", [](){ cout << "Button less music clicked"; }},
        {"buttonMoreMusicAction", [](){ cout << "Button more music clicked"; }},
        {"buttonLessSoundAction", [](){ cout << "Button less sound clicked"; }},
        {"buttonMoreSoundAction", [](){ cout << "Button more sound clicked"; }},
        {"buttonOneAction", []() { cout << "Button 1 clicked"; }},
        {"buttonTwoAction", []() { cout << "Button 2 clicked"; }},
        {"buttonThreeAction", []() { cout << "Button 3 clicked"; }},
        {"buttonFourAction", []() { cout << "Button 4 clicked"; }},
        {"buttonFiveAction", []() { cout << "Button 5 clicked"; }},
        {"buttonSixAction", []() { cout << "Button 6 clicked"; }},
        {"buttonSevenAction", []() { cout << "Button 7 clicked"; }},
        {"buttonEightAction", []() { cout << "Button 8 clicked"; }},
        {"buttonNineAction", []() { cout << "Button 9 clicked"; }}
    };
    
    // Read and draw the options
    if (jsonData.contains("options") && jsonData["options"].contains("image")) {
        for (const auto& item : jsonData["options"]["image"]) {
            int x = item["x"].get<int>();
            int y = item["y"].get<int>();
            int width = item["width"].get<int>();
            int height = item["height"].get<int>();
            string imagePath = item["imagePath"].get<string>();

            draw.drawImage(renderer, x, y, width, height, imagePath.c_str());
        }
    } else if (jsonData.contains("options") && jsonData["options"].contains("text")) {
        for (const auto& item : jsonData["options"]["text"]) {
            int x = item["x"].get<int>();
            int y = item["y"].get<int>();
            string text = item["text"].get<string>();
            int r = item["r"].get<int>();
            int g = item["g"].get<int>();
            int b = item["b"].get<int>();
            int a = item["a"].get<int>();

            draw.drawText(renderer, x, y, text.c_str(), r, g, b, a);
        }
    } else if (jsonData.contains("options") && jsonData["options"].contains("buttons")) {
        for (const auto& item : jsonData["options"]["button"]) {
            int x = item["x"].get<int>();
            int y = item["y"].get<int>();
            int width = item["width"].get<int>();
            int height = item["height"].get<int>();
            string imagePath = item["imagePath"].get<string>();
            string method = item["method"].get<string>();

            draw.createButton(renderer, x, y, width, height, imagePath.c_str(), mouseX, mouseY, clicked, actionMap[method]);
        }
    } else if (jsonData.contains("options") && jsonData["options"].contains("rect")) {
        for (const auto& item : jsonData["options"]["rectangle"]) {
            int x = item["x"].get<int>();
            int y = item["y"].get<int>();
            int width = item["width"].get<int>();
            int height = item["height"].get<int>();
            int r = item["r"].get<int>();
            int g = item["g"].get<int>();
            int b = item["b"].get<int>();
            int a = item["a"].get<int>();

            draw.drawRect(renderer, x, y, width, height, r, g, b, a);
        }
    }
}