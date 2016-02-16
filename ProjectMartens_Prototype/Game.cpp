#include "Game.h"

Game::Game(GLuint width, GLuint height)
{

}

Game::~Game()
{
	for (std::vector<Entity*>::iterator it = cubes.begin(); it != cubes.end(); ++it)
	{
		delete (*it);
	}
	cubes.clear();

	delete camera;
}

void Game::initialize()
{
	// Load shaders
	ResourceManager::LoadShader("VertexShaderSource.txt", "FragmentShaderSource.txt", nullptr, "Default");

	// Projection 
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);

	// Configure shaders
	ResourceManager::GetShader("Default").Use();
	ResourceManager::GetShader("Default").SetInteger("ourTexture", 0);
	ResourceManager::GetShader("Default").SetMatrix4("projection", projection);
	
	//ResourceManager::GetShader("Light").Use();
	//ResourceManager::GetShader("Light").SetInteger("ourTexture", 0);
	//ResourceManager::GetShader("Light").SetMatrix4("projection", projection);

	// Load textures
	ResourceManager::LoadTexture("container.jpg", GL_TRUE, "container");
	ResourceManager::LoadTexture("awesomeface.png", GL_TRUE, "awesomeface");

	camera = new Camera();

	//cubes.push_back(new Entity(ResourceManager::GetShader("Default"), 
	//							ResourceManager::GetTexture("container"), 
	//							glm::vec3(0.0f, 0.0f, 0.0f), 
	//							glm::vec3(5.0f, 100.0f, 0.0f),
	//							glm::vec3(0.15f, 0.15f, 0.15f)));


}

void Game::processInput(GLfloat deltaTime)
{
	// Camera controls
	if (mKeys[GLFW_KEY_W])
		camera->processKeyboardInput(FORWARD, deltaTime);
	if (mKeys[GLFW_KEY_S])
		camera->processKeyboardInput(BACKWARD, deltaTime);
	if (mKeys[GLFW_KEY_A])
		camera->processKeyboardInput(LEFT, deltaTime);
	if (mKeys[GLFW_KEY_D])
		camera->processKeyboardInput(RIGHT, deltaTime);
}

void Game::update(GLfloat deltaTime)
{
	for (std::vector<Entity*>::iterator it = cubes.begin(); it != cubes.end(); ++it) {

		(*it)->update(deltaTime);
	}
}

void Game::render()
{
	glm::mat4 view;
	view = camera->getViewMatrix();
	
	ResourceManager::GetShader("Default").SetMatrix4("view", view);

	for (std::vector<Entity*>::iterator it = cubes.begin(); it != cubes.end(); ++it) {
		
		(*it)->render();
	}
}

void Game::createNewEntity()
{
	cubes.push_back(new Bullet(ResourceManager::GetShader("Default"),
		ResourceManager::GetTexture("awesomeface"),
		camera->getPosition(),
		glm::vec3(5.0f, 100.0f, 0.0f),
		glm::vec3(0.15f, 0.15f, 0.15f), 2.0f, camera->getForward()));
}