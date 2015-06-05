#ifndef __CG_STUDIO_COMMAND_H__
#define __CG_STUDIO_COMMAND_H__

#include "Model.h"

namespace Crystal {
	namespace CG {

class Command {
public:
	Command(Model* model) :
		model(model)
	{}

	void createBox() {
		Math::Space3d<float> space(Math::Vector3d<float>(0, 0, 0), Math::Vector3d<float>(1, 1, 1));

		Math::Bitmap3d bmp(20, 20, 20);
		BitSpace3dSPtr<float> bs(new Math::BitSpace3d<float>(space, bmp));
		bs->setBox();

		model->addBitSpace(bs);

		model->toPolygon();
	}
private:
	Model* model;
};
	}
}

#endif