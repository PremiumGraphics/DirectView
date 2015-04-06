#include "../Graphics/WireFrameRenderer.h"

#include "../ThirdParty/glfw-3.1.1/include/GLFW/glfw3.h"

#include <stdlib.h>
#include <stdio.h>

using namespace Crystal::Graphics;

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	WireFrameRenderer renderer;
	renderer.build();

	Camera<float> camera;
	DisplayList list;

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);


		renderer.render(width, height, camera, list);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

//! [code]