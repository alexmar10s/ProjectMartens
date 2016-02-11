// GLFW.
#include <GLFW/glfw3.h>

// GLM.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CameraDirection
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera();
	~Camera();

	void processMouseInput(double xPosition, double yPosition);
	void processKeyboardInput(CameraDirection direction, GLfloat deltaTime);
	glm::mat4 getViewMatrix();

private:

	void updateCameraVectors();

	glm::mat4 mViewMatrix;

	glm::vec3 mPosition;
	glm::vec3 mFront;
	glm::vec3 mUp;
	glm::vec3 mRight;
	glm::vec3 mWorldUp;

	GLfloat mPreviousXPosition;
	GLfloat mPreviousYPosition;
	GLfloat mYaw;
	GLfloat mPitch;
	GLfloat mMovementSpeed;
	GLfloat mSensitivity;

	bool mFirstMouse;
};