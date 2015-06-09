#ifndef __CRYSTAL_COMMAND_LIGHT_FACTORY_H__
#define __CRSYTAL_COMMAND_LIGHT_FACTORY_H__

#include "../Graphics/Light.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Command {

class LightFactory final : private UnCopyable
{
public:
	Graphics::LightSPtr build() {
		Graphics::LightSPtr l(new Graphics::PointLight());
		lights.push_back(l);
		return l;
	}

	void clear(){ lights.clear(); }

	void remove(Graphics::LightSPtr l) { lights.remove(l); }

	Graphics::LightSPtrList getLights() const { return lights; }

private:
	Graphics::LightSPtrList lights;

};

using LightFactorySPtr = std::shared_ptr< LightFactory >;

	}
}

#endif