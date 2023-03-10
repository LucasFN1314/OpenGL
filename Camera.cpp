#include "Camera.h"
#include<iostream>


Camera::Camera(int width, int height, glm::vec3 position, GLFWwindow* window)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;

	lastX = width / 2;
	lastY = height / 2;
	glfwSetCursorPos(window, width / 2, height / 2);

}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective( glm::radians(FOVdeg), (float)(width/height), nearPlane, farPlane );

	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position -= speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.1f;
	}

	/////////////////////////////////////// CAMERA ROTATION ///////////////////////////////////////

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	
	//std::cout << "X: " << mouseX << std::endl;
	float rotY = sensitivity * (float)(mouseY - (height / 2)) / height;
	float rotX = sensitivity * (float)(mouseX - (width / 2)) / width;

	glm::vec3 nOrientation = glm::rotate(Orientation, glm::radians(-rotY), glm::normalize(glm::cross(Orientation, Up)));
	// Y
	if (!((glm::angle(nOrientation, Up) <= glm::radians(5.0f)) or (glm::angle(nOrientation, -Up)) <= -glm::radians(5.0f))) {
		Orientation = nOrientation;
	}
	// X
	Orientation = glm::rotate(Orientation, glm::radians(-rotX), Up);

	glfwSetCursorPos(window, width / 2, height / 2);

	/////////////////////////////////////// CAMERA ROTATION ///////////////////////////////////////
}
