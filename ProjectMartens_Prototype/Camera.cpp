#include "Camera.h"

Camera::Camera()
{
	mPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	mWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	mPreviousXPosition= 800 / 2.0;
	mPreviousYPosition = 600 / 2.0;
	mYaw = -90.0f;
	mPitch = 0.0f;
	mMovementSpeed = 5.0f;
	mSensitivity = 0.05f;
	mFirstMouse = true;	

	updateCameraVectors();
}

Camera::~Camera()
{

}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

void Camera::processMouseInput(double xPosition, double yPosition)
{
	if (mFirstMouse)
	{
		mPreviousXPosition = xPosition;
		mPreviousYPosition = yPosition;
		mFirstMouse = false;
	}

	GLfloat xOffset = xPosition - mPreviousXPosition;
	GLfloat yOffset = mPreviousYPosition - yPosition;
	mPreviousXPosition = xPosition;
	mPreviousYPosition = yPosition;

	xOffset *= mSensitivity;
	yOffset *= mSensitivity;

	mYaw += xOffset;
	mPitch += yOffset;

	if (mPitch > 89.0f)
		mPitch = 89.0f;
	if (mPitch < -89.0f)
		mPitch = -89.0f;

	updateCameraVectors();
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::processKeyboardInput(CameraDirection direction, GLfloat deltaTime)
{
	GLfloat velocity = mMovementSpeed * deltaTime;
	if (direction == FORWARD)
		mPosition += mFront * velocity;
	if (direction == BACKWARD)
		mPosition -= mFront * velocity;
	if (direction == LEFT)
		mPosition -= mRight * velocity;
	if (direction == RIGHT)
		mPosition += mRight * velocity;

	mPosition.y = 0.0f;
}

// Calculates the front vector from the Camera's (updated) Eular Angles
void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	front.y = sin(glm::radians(mPitch));
	front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	mFront = glm::normalize(front);
	
	// Also re-calculate the Right and Up vector
	mRight = glm::normalize(glm::cross(mFront, mWorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	mUp = glm::normalize(glm::cross(mRight, mFront));
}