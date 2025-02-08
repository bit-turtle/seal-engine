// Seal Engine Implementation
#include <seal/Engine.hpp>

int main() {
    // Game Initialization and Window Creation
    init();
    // Default window if not created
    if (window == nullptr) {
        window = new sf::RenderWindow(sf::VideoMode({640,360}), "Seal Engine Game");
    }
    while (window->isOpen()) {
        // Main Loop
    }
    return EXIT_SUCCESS;
}

void seal_frame() {

}
