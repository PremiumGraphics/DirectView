#ifndef __CRYSTAL_COMMAND_LIGHT_FACTORY_H__
#define __CRSYTAL_COMMAND_LIGHT_FACTORY_H__

#include "../Graphics/Light.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Command {

template<typename T>
class LightFactory final : private UnCopyable
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
using LightFactorySPtr = std::shared_ptr< LightFactory<T> >;

	}
}

#endif