#include "../Shader/PointRenderer.h"

#include "../ThirdParty/glfw-3.1.1/include/GLFW/glfw3.h"

#include "../Graphics/Polygon.h"

#include <stdlib.h>
#include <stdio.h>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

class PointRendererTest {
public:
	int test();
};

int PointRendererTest::test(void)
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

	//WireFrameRenderer renderer;
	PointRenderer renderer;
	renderer.build();

	Camera<float> camera;
	Vector3dVector positions;
	positions.push_back(Vector3d(0.0, 0.0, -5.0));
	positions.push_back(Vector3d(1.0, 0.0, -5.0));
	positions.push_back(Vector3d(1.0, 1.0, -5.0));
	DisplayList list(positions);
	std::vector<float> colors{ 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };
	const std::vector< std::vector< unsigned int > > ids = { { 0, 1, 2 } };
	list.setIds(ids);
	list.setColors(colors);

	while (!glfwWindowShouldClose(window)) {
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		//ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		renderer.render(width, height, &camera, list);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}