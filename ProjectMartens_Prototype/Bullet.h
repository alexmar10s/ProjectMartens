#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(Shader &shader, Texture2D &texture1, glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale, GLfloat speed, glm::vec3 initialVelocity);
	~Bullet();

	virtual void update(GLfloat deltaTime);

protected:
	glm::vec3 mVelocity;
	GLfloat mSpeed;
};

#endif