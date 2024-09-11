// FrameSeal Engine v0.01
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#ifndef ENGINE_HPP
#define ENGINE_HPP

namespace seal {	// The seal Namespace contains all of the Engine 

	// OpenGL Definitions

	class Shader {	// A class to describe a shader
		public:
		unsigned int id;
		// Create shader from file in ./shaders
		Shader(const char* vertexFilename, const char* fragmentFilename);
		// Activate shader and deactivate other shaders
		void use();
		// Functions to pass values to shader
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
	};

	// Engine Definitions

	void start(int width, int height, const char* title);	// Start the Engine and Create Game Window

	void stop();	// Shutdown the Engine

	typedef float Time;	// Defines a Type to keep track of Time in Seconds
  
	typedef float Distance;	// Defines a Type to represent Distance in Meters

	typedef float Speed;	// Defines a Type to represent Speed in Meters a Second

	struct Vector {		// Vector structure
		float x;	// X Value
		float y;	// Y Value
		float z;	// Z Value
	};

	typedef Vector Position;	// Defines a Type to store a Position Vector in Meters

	typedef Vector Velocity;	// Defines a Type to store a Velocity Vector in Meters a Second

	typedef Vector Rotation;	// Defines a Type to store a Rotation Vector in Radians

	typedef Vector RotationalVelocity;	// Defines a Type to store a Rotational Velocity Vector in Radians a Second

	typedef Vector Hitbox;	// Defines a Type to store a Hitbox Size in Meters
  
	struct KeyboardInput {	// Defines a struct to represent all the keys the keyboard
		
		// Special Keys
		bool esc;
		bool shift;
		bool ctrl;
		bool alt;
		bool tab;
		bool enter;
		bool backspace;
		bool space;

		// Arrow Keys
		bool uparrow;
		bool leftarrow;
		bool downarrow;
		bool rightarrow;

		// Letter Keys
		bool q;
		bool w;
		bool e;
		bool r;
		bool t;
		bool y;
		bool u;
		bool i;
		bool o;
		bool p;
		bool a;
		bool s;
		bool d;
		bool f;
		bool g;
		bool h;
		bool j;
		bool k;
		bool l;
		bool z;
		bool x;
		bool c;
		bool v;
		bool b;
		bool n;
		bool m;

		// Number Keys
		bool one;
		bool two;
		bool three;
		bool four;
		bool five;
		bool six;
		bool seven;
		bool eight;
		bool nine;
		bool zero;
		
		// Punctuation Keys
		bool comma;
		bool period;
		bool backslash;
		bool semicolon;
		bool quote;
		bool leftbracket;
		bool rightbracket;
		bool slash;
		bool dash;
		bool equals;
		bool tilde;

		// Function Keys
		bool f1;
		bool f2;
		bool f3;
		bool f4;
		bool f5;
		bool f6;
		bool f7;
		bool f8;
		bool f9;
		bool f10;
		bool f11;
		bool f12;
	};

	struct MouseInput {	// Defines a structure to represent mouse state
		int x;
		int y;
		int xspeed;
		int yspeed;
		int wheelspeed;
		bool right;
		bool middle;
		bool left;
	};
 
	struct Input {	// User Input Structure
		KeyboardInput Keyboard;
		MouseInput Mouse;
	};

	// Global Functions
	void setinitfunc( void (*initfunc)(void) );	// Set Global Init Function
	void setframefunc( void (*framefunc)(Time, Input) );	// Set Global Frame Function
	
	// Sprites
	class Sprite {					// Sprite Class
		public:					// All Members are Public
		Sprite() {}				// Base Sprite Constructor is Empty
		int id;					// Sprite Identifier (Set by Game Engine)
		Position position;			// Sprite Position
		Rotation rotation;			// Sprite Rotation
		Velocity velocity;			// Sprite Velocity
		RotationalVelocity rotationvelocity;	// Sprite Rotational Velocity
		Hitbox hitbox;				// Sprite Hitbox centered around Sprite Position
		bool destroy = false;			// Destroy Sprite at end of frame
		bool physics = true;			// Enable Built In Movement and Collision Physics For This Sprite

		bool collisions = true;			// Enable Collisions For This Sprite [Built-In Physics]
		bool collidable = true;			// Other Sprites Can Collide With Sprite
		bool pushable = true;			// Treat Sprite as Pushable (Other Sprites Can Push Sprite) [Built-In Physics]
		virtual void frame(Time deltatime, Input input) {	// frame(Time,Input) is called every frame for each Sprite (deltatime is passed)
		}					// Base Frame Handler is Empty
	};

	void createSprite(Sprite* sprite);  // Create a new Sprite

	Sprite* getSprite(int id);	// Get Sprite By ID from Internal Sprite List
	
	std::vector<Sprite*> getSpriteList();	// Get List of All Sprites

	Position add(Position position, Velocity velocity, Time scale); // Add Scaled Velocity to Position

	Position move(Position position, Rotation rotation, Speed speed, Time scale);	// Move Position in Direction with Speed scaled by Time

}

#endif
