#include "engine.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

// Implementations

namespace seal {

	// OpenGL
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
	// Shader Class
	Shader::Shader(const char* vertexFilename, const char* fragmentFilename) {
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vertexFile;
		std::ifstream fragmentFile;
		// Enable Exception
		vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			// Open Shader Files
			vertexFile.open(vertexFilename);
			fragmentFile.open(fragmentFilename);
			std::stringstream vertexStream, fragmentStream;
			// Read Shader Files
			vertexStream << vertexFile.rdbuf();
			fragmentStream << fragmentFile.rdbuf();
			// Close Shader Files
			vertexFile.close();
			fragmentFile.close();
			// Load Streams into Strings
			vertexCode = vertexStream.str();
			fragmentCode = fragmentStream.str();
		}
		catch(std::ifstream::failure error) {
			std::cout << "Error: Shader Files Not Found! ( " << vertexFilename << ", " << fragmentFilename << ")"  << std::endl;
		}
		const char* vertexShader = vertexCode.c_str();
		const char* fragmentShader = fragmentCode.c_str();
		// Compile Shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];
		// Compile Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexShader, NULL);
		glCompileShader(vertex);
		// Log Errors
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "Error: Vertex Shader Compilation Failed!\n" << infoLog << std::endl;
		};
		// Compile Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentShader, NULL);
		glCompileShader(fragment);
		// Log Errors
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "Error: Fragment Shader Compilation Failed!\n" << infoLog << std::endl;
		}
		// Link Shaders to Program
		// Global Shader program ID
		id = glCreateProgram();
		glAttachShader(id, vertex);
		glAttachShader(id, fragment);
		glLinkProgram(id);
		// Log Errors
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if(!success) {
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			std::cout << "Error: Shader Program Failed to Link!\n" << infoLog << std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	void Shader::use(void) {
		glUseProgram(id);
	}
	void Shader::setBool(const std::string &name, bool value) const {
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
	}
	void Shader::setInt(const std::string &name, int value) const {
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}
	void Shader::setFloat(const std::string &name, float value) const {
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}

	// Global Functions
	bool initfuncset = false;
	void (*initfunction)(void);
	void setinitfunc( void (*initfunc)(void) ) {
		initfunction = initfunc;
		initfuncset = true;
	}

	bool framefuncset = false;
	void (*framefunction)(Time, Input);
	void setframefunc( void (*framefunc)(Time, Input) ) {
		framefunction = framefunc;
		framefuncset = true;
	}
	
	// Sprite Functions
	int nextid = 0;
	std::vector<Sprite*> sprites;
	
	void createSprite(Sprite* sprite) {
		sprite->id = nextid++;
		sprites.push_back(sprite);
	}

	Sprite* getSprite(int id) {
		for ( Sprite* sprite : sprites )
			if ( sprite->id == id ) return sprite;
		return nullptr;
	}

	std::vector<Sprite*> getSpriteList() {
		return sprites;
	}

	// Coordinate Functions
	Position add(Position position, Velocity velocity, Time scale) {
		return {
			position.x + velocity.x * scale,
			position.y + velocity.y * scale,
			position.z + velocity.z * scale,
		};
	}

	Position move(Position position, Rotation rotation, Speed speed, Time scale) {
		return { 
			(Distance) ((cos(rotation.x) * sin(rotation.z)) * (speed * scale)),
			(Distance) ((sin(rotation.x)) * (speed * scale)),
			(Distance) ((cos(rotation.x) * cos(rotation.z)) * (speed * scale)),
		};
	}

	// Input Functions
	
	Input currentinput;

	void processInput(GLFWwindow* window) {
		// Write input into apropriate variables
		// input::keyboard
		// input::mouse

		// Close on [Esc]
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		// Tell OpenGL the window size changed
		glViewport(0, 0, width, height);
	}

	void start(int width, int height, const char* title) {
		// Setup GLFW
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		// Apple Specific Stuff
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL) {
			std::cout << "Error: Failed to Create Game Window with GLFW" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		
		// Setup GLAD (Load OpenGL)
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initalize GLAD (OpenGL)" << std::endl;
			return;
		}

		// Test Verticies
		float vertices[] = {
			1.0f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		// Setup OpenGL
		glViewport(0, 0, width, height);
		// Start Copied Code
		// build and compile our shader program
		// vertex shader
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "Error: Vertex Shader Compilation Failed\n" << infoLog << std::endl;
		}
		// fragment shader
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		// check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "Error: Fragment Shader Compilation Failed\n" << infoLog << std::endl;
		}
		// link shaders
		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "Error: Shader Program Linking Failed\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		
		// Buffers
		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0); 

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0); 

		// Setup Engine
		sprites.clear();
		nextid = 0;

		if (initfuncset) initfunction();

		Time deltatime = 0;
		while (!glfwWindowShouldClose(window)) {
			// Process Input
			processInput(window);

			// Global Frame Function
			if (framefuncset) framefunction(deltatime, currentinput);

			// Sprite Frame Functions
			for ( Sprite* sprite : sprites )
				sprite->frame(deltatime, currentinput);

			// Sprite Physics (Minecraft Style Non Rotating Hitbox)
			for ( Sprite* sprite : sprites )
				if (sprite->collisions)
					for ( Sprite* collisionsprite : sprites )
						if (sprite->collidable)

			// Draw Stuff
			glClearColor(0.f, 0.f, 0.f, 1.f);	// Black Background
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			vertices[0] += 0.01f;

			// Temporary Renderer
			for ( Sprite* sprite : sprites ) {
				
			}

			// Destroy Sprites
			for ( int sprite = 0; sprite < sprites.size(); sprite++ ) {
				if (sprites.at(sprite)->destroy) {
					delete sprites.at(sprite);
					sprites.erase(sprites.begin()+sprite);
					sprite--;
				}
			}


			// Update Window
			glfwSwapBuffers(window);
			
			// Get Input
			glfwPollEvents();
		}
	}
}
