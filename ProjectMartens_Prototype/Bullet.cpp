#include "Bullet.h"


Bullet::Bullet(Shader &shader, Texture2D &texture1, glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale, GLfloat speed, glm::vec3 initialVelocity)
{
	mShader = shader;
	mTexture1 = texture1;
	mPosition = position + (initialVelocity / 2.0f);
	mEularAngles = eulerAngles;
	mScale = scale;
	mSpeed = speed;
	mVelocity = initialVelocity;
	initRenderData();
}

Bullet::~Bullet()
{
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &mVao);
	glDeleteBuffers(1, &mVbo);
}

void Bullet::update(GLfloat deltaTime)
{
	mPosition = mPosition + (mVelocity * mSpeed) * deltaTime;
	
	std::cout << "Hello from Bullet" << std::endl;
}