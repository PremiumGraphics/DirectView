#ifndef __CG_STUDIO_COMMAND_H__
#define __CG_STUDIO_COMMAND_H__

#include "Model.h"

namespace Crystal {
	namespace CGS {


class MainCommand {
public:
	explicit MainCommand(Model* model) :
		model(model)
	{
		sf = model->getSpaceFactory();
	}

	void createBox(const unsigned int resx, const unsigned int resy, const unsigned int resz) {
		model->getSpaceFactory()->createBox(resx, resy, resz);
		model->toPolygon();
	}

	void createSphere(const unsigned int resx, const unsigned int resy, const unsigned int resz) {
		model->getSpaceFactory()->createSphere(resx, resy, resz);
		model->toPolygon();
	}

	void createCylinder(const unsigned int resx, const unsigned int resy, const unsigned int resz) {
		model->getSpaceFactory()->createCylinder(resx, resy, resz);
		model->toPolygon();
	}

private:
	Model* model;
	SpaceFactory* sf;
};

class BooleanCommand {
public:
	BooleanCommand(const BitSpace3dSPtr<float>& bs1, const BitSpace3dSPtr<float>& bs2) :
		bs1(bs1),
		bs2(bs2)
	{
	}

	void and();
private:
	BitSpace3dSPtr<float> bs1;
	BitSpace3dSPtr<float> bs2;
};
	}
}

#endif