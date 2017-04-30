#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer
{
private:
	GLFWerrorfun error_callback;
	GLFWkeyfun key_callback;
public:
	Renderer(GLFWerrorfun, GLFWkeyfun);
	~Renderer();

	void setVertexBuffer(GLuint* bufferPtr, int arrayMemory, float* vertices);
	GLuint setShader(GLenum shaderType, const GLchar* shaderSource, GLint* shaderStatus);
	void runGlLoop(const GLchar* vertexSource, const GLchar* fragmentSource);
};