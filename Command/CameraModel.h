#ifndef __CRYSTAL_COMMAND_CAMERA_MODEL_H__
#define __CRYSTAL_COMMAND_CAMERA_MODEL_H__

#include "Object.h"

#include "../Graphics/Camera.h"

namespace Crystal {
	namespace Model {

template<typename T>
class CameraObject : public Object {
public:
	explicit CameraObject(Graphics::CameraSPtr<T>& c) :
		camera(c)
	{}

	Graphics::CameraSPtr<T> getCamera() const { return camera; }

	virtual void move(const Math::Vector3d<float>& vector){
		camera->move(vector);
	}

	Type getType() const { return Type::Camera; }

private:
	Graphics::CameraSPtr<T> camera;

};

template<typename T>
using CameraObjectSPtr = std::shared_ptr < CameraObject<T> > ;

/*
template<typename T>
class CameraModel {

};
*/
	}
}

#endif