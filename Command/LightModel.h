#ifndef __CRYSTAL_COMMAND_LIGHT_MODEL_H__
#define __CRSYTAL_COMMAND_LIGHT_MODEL_H__

#include "../Graphics/Light.h"

#include "../Util/UnCopyable.h"

#include "Object.h"
#include "Factory.h"

namespace Crystal {
	namespace Command {

template<typename T>
class LightObject : public Object
{
	LightObject(const Graphics::LightSPtr<T>& light) :
		light( light )
	{
	}

	Type getType() const { return Type::Light; }

	Graphics::LightSPtr<T> getLight() const { return light; }

private:
	Graphics::LightSPtr<T> light;
};

template<typename T>
using LightObjectSPtr = std::shared_ptr < LightObject<T> >;

template<typename T>
using LightObjectSPtrList = std::list < LightObjectSPtr<T> > ;

template<typename T>
class LightModel final : public ModelBase
{
public:
	/*
	Graphics::LightSPtr<T> build() {
		Graphics::LightSPtr<T> l(new Graphics::PointLight<T>());
		lights.push_back(l);
		return l;
	}
	*/

	void clear(){
		ModelBase::clear();
		lights.clear();
	}

	void remove(Graphics::LightSPtr<T> l) { lights.remove(l); }

	void remove(const unsigned int id) override {
		;

	}

	LightObjectSPtrList<T> getLights() const { return lights; }

private:
	LightObjectSPtrList<T> lights;
};

template<typename T>
using LightModelSPtr = std::shared_ptr< LightModel<T> >;

	}
}

#endif