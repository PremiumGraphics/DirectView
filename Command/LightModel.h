#ifndef __CRYSTAL_COMMAND_LIGHT_MODEL_H__
#define __CRSYTAL_COMMAND_LIGHT_MODEL_H__

#include "../Graphics/Light.h"

#include "../Util/UnCopyable.h"

#include "Object.h"

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
class LightModel final : private UnCopyable
{
public:
	Graphics::LightSPtr<T> build() {
		Graphics::LightSPtr<T> l(new Graphics::PointLight<T>());
		lights.push_back(l);
		return l;
	}

	void clear(){ lights.clear(); }

	void remove(Graphics::LightSPtr<T> l) { lights.remove(l); }

	Graphics::LightSPtrList<T> getLights() const { return lights; }

private:
	Graphics::LightSPtrList<T> lights;
};

template<typename T>
using LightModelSPtr = std::shared_ptr< LightModel<T> >;

	}
}

#endif