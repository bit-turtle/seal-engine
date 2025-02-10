// Seal Engine Include File
#ifndef SealEngine
#define SealEngine

// Includes
#include <SFML/Graphics.hpp>

// Render Window
sf::RenderWindow* getWindow();

// Render Target (Default RenderTarget)
sf::RenderTexture* getTarget();

/* All times are in seconds ("delta" for example) */

// Game initialization
void init();
// Code to run every frame
void frame(float delta);

#endif	// SealEngine
