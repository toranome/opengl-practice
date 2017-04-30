#include "stdafx.h"
#include "Debug.h"
#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Renderer::Renderer(GLFWerrorfun errorFunction, GLFWkeyfun keyFunction)
{
	error_callback = errorFunction;
	key_callback = keyFunction;
}

Renderer::~Renderer()
{
}

void Renderer::setVertexBuffer(GLuint* bufferPtr, int arrayMemory, float* vertices)
{
	glGenBuffers(1, bufferPtr);
	glBindBuffer(GL_ARRAY_BUFFER, *bufferPtr);
	glBufferData(GL_ARRAY_BUFFER, arrayMemory, vertices, GL_STATIC_DRAW);
}

GLuint Renderer::setShader(GLenum shaderType, const GLchar* shaderSource, GLint* shaderStatus)
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, shaderStatus);

	return shader;
}

void Renderer::runGlLoop(const GLchar* vertexSource, const GLchar* fragmentSource) {
	if (!glfwInit())
	{
		std::cout << "FAIL: glfw not initialised";
		exit(EXIT_FAILURE);
	}

	glfwSetErrorCallback(Renderer::error_callback);
	GLFWwindow* window = glfwCreateWindow(800, 600, "WHOOHOO!", NULL, NULL);

	glfwSetKeyCallback(window, Renderer::key_callback);

	if (!window)
	{
		std::cout << "FAIL: window not created";
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	GLenum err = glewInit();
	std::cout << "GLEW Errors: " << err << "\n";

	double time = glfwGetTime();
	glfwSwapInterval(1);

	float vertices[] = {
		-0.0f,  0.5f, // Vertex 1 (X, Y)
		0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f  // Vertex 3 (X, Y)
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vertexBuffer;
	GLint positiveAttribute;
	GLuint shaderProgram;

	GLuint fragmentShader;
	GLint fragmentShaderStatus;
	GLuint vertexShader;
	GLint vertexShaderStatus;

	setVertexBuffer(&vertexBuffer, sizeof(vertices), vertices);

	vertexShader = setShader(GL_VERTEX_SHADER, vertexSource, &vertexShaderStatus);
	fragmentShader = setShader(GL_FRAGMENT_SHADER, fragmentSource, &fragmentShaderStatus);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	positiveAttribute = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(positiveAttribute);
	glVertexAttribPointer(positiveAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);

	std::cout << "Vertex Shader Compiled: " << vertexShaderStatus << "\n";
	std::cout << "Fragment Shader Compiled: " << fragmentShaderStatus << "\n";
	std::cout << "Error Code: " << glGetError() << "\n";

	while (!glfwWindowShouldClose(window))
	{
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, width, height);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cout << "Error Code: " << glGetError() << "\n";

	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vao);

	glfwDestroyWindow(window);
	glfwTerminate();
}