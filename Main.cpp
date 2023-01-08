#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "VAO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "Texture.h"
#include "Camera.h"

#include<glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

using namespace std;
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLfloat vertices[] = {
		-0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,
		-0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 1.0f,
		 0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,
		 0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 0.0f,
		 0.0f,  1.0f,  0.0f,		0.92f, 0.86f, 0.76f,		2.5f, 5.0f,

	};

	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4,
	};

	GLuint width = 800;
	GLuint height = 600;

	GLFWwindow* window = glfwCreateWindow(width, height, "OPEN GL", NULL, NULL);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (window == NULL) {
		cout << "FAILED TO CREATE WINDOW" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);

	//////////////////////////////////////////////////////////////////////////////////////////////
	Shader shaderProgram("vertex_shader.vs", "fragment_shader.fs");
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6*sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	//////////////////////////////////////////////////////////////////////////////////////////////

	Texture wall("Resources/container.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	wall.textUnit(shaderProgram, "tex0", 0);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), window);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// RENDER
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.activate();
		camera.Inputs(window);
		camera.updateMatrix(60.0f, 0.1f, 100.0f);
		camera.Matrix(shaderProgram, "camMatrix");
		/////////////

		wall.bind();
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	wall.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}