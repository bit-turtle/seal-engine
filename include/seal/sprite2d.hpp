// Seal Engine Sprite2D Class
#ifndef SealEngineSprite2D
#define SealEngineSprite2D

// Includes
#include <seal/vector2.hpp>
#include <seal/texture.hpp>
#include <seal/shader.hpp>

// Base class for all 2d sprites
class Sprite2D {
public:
	// Sprite Variables
	Vector2 position;
	Vector2 velocity;
	bool gravity;
	// Sprite Texture
	Texture* texture = nullptr;
	// Sprite Shader
	Shader* shader = nullptr;
	// Sprite Functions
	Sprite2D() {
		// Sprite initialization
	}
	virtual void frame(float delta) {
		// Sprite code to run every frame
	}
};

// Adds a 2d sprite to the scene
// Returns the newly added sprite's id
unsigned addSprite2D(Sprite2D* sprite);

// Gets a 2d sprite by id from the scene
// Returns a pointer to the sprite or a nullptr if the sprite doesn't exist
Sprite2D* getSprite2D(unsigned id);

#endif	// SealEngineSprite2D
