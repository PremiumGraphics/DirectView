#include "stdafx.h"

#include "Model.h"

#include <fstream>

using namespace Crystal::CG;

using namespace Crystal::Graphics;


Model::Model() :
	camera( new Camera<float>() )
{
	lights.push_back(Light());
}

Model::~Model()
{
}

void Model::clear()
{
	materials.clear();
	lights.clear();
}