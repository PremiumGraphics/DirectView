#ifndef __CRYSTAL_COMMAND_SCALAR_SPACE_TRANSFORM_COMMAND_H__
#define __CRYSTAL_COMMAND_SCALAR_SPACE_TRANSFORM_COMMAND_H__

#include "../Math/ScalarSpace.h"

namespace Crystal {
	namespace Command {

template<typename T>
class ScalarSpaceTransformCommand final
{
public:
	ScalarSpaceTransformCommand() = default;

	~ScalarSpaceTransformCommand() = default;

	ScalarSpaceTransformCommand& move(const Math::Vector3d<float>& vector) {
		for (auto& b : spaces) {
			b->move(vector);
		}
		return (*this);
	}

	ScalarSpaceTransformCommand& scale(const Math::Vector3d<float>& scale) {
		for (auto& b : spaces) {
			b->scale(scale);
		}
		return (*this);
	}


	Math::ScalarSpace3dSPtrList<T> getSpaces() const { return spaces; }

private:
	Math::ScalarSpace3dSPtrList<T> spaces;
};
	}
}

#endif