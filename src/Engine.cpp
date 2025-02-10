// Seal Engine Implementation
#include <seal/Engine.hpp>

sf::RenderWindow window;
sf::RenderWindow* getWindow() {
    return &window;
}

sf::RenderTexture target;
sf::RenderTexture* getTarget() {
    return &target;
}

// Main Function
int main() {
    // Game Initialization
    init();
    // Default window if not created
    if (!window.isOpen()) {
        window.create(sf::VideoMode({640,360}), "Seal Engine Game");
    }
    while (window.isOpen()) {
        // Main Loop
    }
    return EXIT_SUCCESS;
}

// Render Frame
void seal_frame() {

}
