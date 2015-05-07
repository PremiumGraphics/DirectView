#include "Scene2dRendererTest.h"


#include "../Shader/Space2dRenderer.h"

#include "../ThirdParty/glfw-3.1.1/include/GLFW/glfw3.h"

#include "../Graphics/Polygon.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;


int Scene2dRendererTest::test(void)
{
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	Space2dRenderer renderer;
	renderer.build();

	int n = 0;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &n);
	std::cout << "max texture units = " << n << std::endl;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &n);
	std::cout << "max texture size = " << n << std::endl;
	glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &n);
	std::cout << "max 3d texture size = " << n << std::endl;

	Camera<float> camera;
	Vector3dVector positions;
	positions.push_back(Vector3d(0.0, 0.0, -5.0));
	positions.push_back(Vector3d(1.0, 0.0, -5.0));
	positions.push_back(Vector3d(1.0, 1.0, -5.0));
	//DisplayList list(positions);

	while (!glfwWindowShouldClose(window)) {
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		//ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		renderer.render(width, height, &camera, Vector3d::toArray(positions));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}