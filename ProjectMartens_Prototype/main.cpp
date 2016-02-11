/* BASE PROJECT */

// GLEW.
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW.
#include <GLFW/glfw3.h>

// SOIL.
#include <SOIL\SOIL.h>

// GLM.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes.
#include <iostream>
#include "Game.h"
#include "InputManager.h"

// Function prototypes.
void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xPosition, double yPosition);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Other vars.
Game game(800, 600);

// Input vars
bool keys[1024];

// Globals
float deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main() 
{
	// Inititialize GLFW.
	glfwInit();

	// Set options. More info. http://www.learnopengl.com/#!Getting-Started/Hello-Window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create the Window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	
	// Check if window creation is sucessful, otherwise terminate glfw and exit.
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return - 1;
	}

	// Tell GLFW to make the context of our window the main context on the current thread.
	glfwMakeContextCurrent(window);

	// Mouse input.
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize GLEW
	glewExperimental = GL_TRUE;

	// Check if glew initilization is sucessful, otherwise exit.
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Tell OpenGL size of rendering window,
	// so OpenGL knows how we want to display 
	// the data and coordinates with respect to the window.
	glViewport(0, 0, 800, 600);

	// Register callbacks.
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	game.initialize();
	game.setState(GAME_ACTIVE);

	// Enable Z buffer depth test.
	glEnable(GL_DEPTH_TEST);

	// Game Loop. Keeps runnin GLFW until told to stop.
	while (!glfwWindowShouldClose(window))
	{
		// Track deltaTime
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check to see if any events have been triggered, and calls corresponding callack methods.
		glfwPollEvents();
		game.processInput(deltaTime);

		// Render here.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // State setting function.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // State using function.

		game.update(deltaTime);
		game.render();
		
		// Swap screen buffers for specified window.
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	
	return 0;
}

/*
Call back for keyboard interaction.
*/
void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mode)
{	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	// TODO: Make a getter to mKeys, make private.
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			game.mKeys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			game.mKeys[key] = false;
		}
	}
}

void mouse_callback(GLFWwindow* window, double xPosition, double yPosition)
{
	game.getCamera()->processMouseInput(xPosition, yPosition);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		std::cout << "CLICKED" << std::endl;
	}
}
