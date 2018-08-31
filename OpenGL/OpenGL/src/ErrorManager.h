#pragma once

#include <GL/glew.h>

#define ASSERT(x) if(!(x)) __debugbreak();

#ifdef  DEBUG
#define GLCall(x) ErrorManager::GLClearError(); x; ASSERT(ErrorManager::GLLogCall(#x, __FILE__, __LINE__)); 
#else
#define GLCall(x) x;
#endif //  DEBUG



class ErrorManager {

public:
	static void GLClearError();
	static bool GLLogCall(const char* function, const char* file, int line);
};