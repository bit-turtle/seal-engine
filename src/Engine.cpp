// Seal Engine Implementation
#include <seal/Engine.hpp>

sf::RenderWindow* window = nullptr;
sf::RenderWindow* getWindow() {
    return window;
}

sf::RenderTexture* target = nullptr;
sf::RenderTexture* getTarget() {
    return target;
}

// Main Function
int main() {
    // Game Initialization
    init();
    // Default Window Creation
    if (window == nullptr)
        window = new sf::RenderWindow(sf::VideoMode({640,360}), "Seal Engine Game");
    // Game Initialization
    sf::Clock clock;
    while (window->isOpen()) {
        // Process Deltatime
        sf::Time delta = clock.restart();
        // Poll Events
        while (const std::optional event = window->pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    window->close();
        }

        // Update Game
        frame(delta);

        // Render
        window->clear(sf::Color::Black);

        // Draw Stuff
        

        window->display();
    }
    return EXIT_SUCCESS;
}

// Render Frame
void seal_frame() {

}
