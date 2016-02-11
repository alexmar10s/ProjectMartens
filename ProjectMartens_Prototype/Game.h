#include <vector>
#include <string>

#include "Entity.h"
#include <GLFW/glfw3.h>

#include "ResourceManager.h"
#include "Camera.h"

// GLM.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
	public:
		Game(GLuint width, GLuint height);
		~Game();

		GameState getState() { return mState; }
		void setState(GameState state) { mState = state; }

		Camera* getCamera(){ return camera; }
		
		GLboolean mKeys[1024];

		void initialize();
		void processInput(GLfloat deltaTime);
		void update(GLfloat deltaTime);
		void render();
		void createNewEntity(glm::vec3 position, std::string shaderName);

	private:
		// Game state
		GameState mState;

		GLuint mWidth, mHeight;
		std::vector<Entity*> cubes;
		Camera* camera;
};