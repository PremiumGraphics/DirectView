#ifndef __CRYSTAL_COMMAND_COMMAND_H__
#define __CRYSTAL_COMMAND_COMMAND_H__

#include "Model.h"

namespace Crystal {
	namespace Command {


class MainCommand {
public:
	explicit MainCommand(Model* model) :
		model(model)
	{
		sf = model->getBitSpaceFactory();
	}

	void createBox(const unsigned int resx, const unsigned int resy, const unsigned int resz) {
		model->getBitSpaceFactory()->createBox(resx, resy, resz);
		model->toPolygon();
	}

	void createSphere(const unsigned int resx, const unsigned int resy, const unsigned int resz) {
		model->getBitSpaceFactory()->createSphere(resx, resy, resz);
		model->toPolygon();
	}

	void createCylinder(const unsigned int resx, const unsigned int resy, const unsigned int resz) {
		model->getBitSpaceFactory()->createCylinder(resx, resy, resz);
		model->toPolygon();
	}

private:
	Model* model;
	BitSpaceFactory* sf;
};
	}
}

#endif