#include "../Shader/WireFrameRenderer.h"

#include "../ThirdParty/glfw-3.1.1/include/GLFW/glfw3.h"

#include "../Graphics/Polygon.h"

#include <stdlib.h>
#include <stdio.h>

#include "WireFrameRendererTest.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;


int main(void)
{
	WireFrameRendererTest test;
	return test.test();
}