// Seal Engine Shader Class
#ifndef SealEngineShader
#define SealEngineShader

// Includes
#include <string>

// Class to represent shaders
class Shader {
public:
	// Shader Variables
	unsigned id;
	// Shader Functions
	Shader(std::string vertexpath, std::string fragmentpath);
};

#endif	// SealEngineShader
