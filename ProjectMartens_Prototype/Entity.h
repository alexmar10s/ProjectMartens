#ifndef ENTITY_H
#define ENTITY_H

#include "Texture.h"
#include "Shader.h"
#include <SOIL\SOIL.h>
#include <GL/glew.h>
// GLFW.
#include <GLFW/glfw3.h>

// GLM.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

class Entity
{
public:

	Entity(Shader &shader);
	Entity(Shader &shader, Texture2D &texture1, glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale);
	~Entity();

	void render();
	virtual void update(GLfloat deltaTime);

protected:

	void initRenderData();
	void calculateModelMatrix(glm::mat4* model);

	Shader mShader;
	GLuint mVao;
	GLuint mVbo;

	Texture2D mTexture1;
	glm::vec3 mPosition;
	glm::vec3 mEularAngles;
	glm::vec3 mScale;
};

#endif