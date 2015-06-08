#ifndef __CRYSTAL_BIT_SPACE_TRANSFORM_COMMAND_H__
#define __CRYSTAL_BIT_SPACE_TRANSFORM_COMMAND_H__

#include "../Math/BitSpace.h"

#include <list>

namespace Crystal {
	namespace Command {

class BitSpaceTransformCommand
{
public:
	BitSpaceTransformCommand() = default;

	~BitSpaceTransformCommand() = default;

	BitSpaceTransformCommand& add(const Math::BitSpace3dSPtr<float>& space) {
		spaces.push_back(space);
		return (*this);
	}

	BitSpaceTransformCommand& remove(const Math::BitSpace3dSPtr<float>& space) {
		spaces.remove(space);
		return (*this);
	}

	BitSpaceTransformCommand& clear() {
		spaces.clear();
		return (*this);
	}

	BitSpaceTransformCommand& not() {
		for (auto& b : spaces) {
			b->not();
		}
		return (*this);
	}

	BitSpaceTransformCommand& and() {
		if (spaces.size() <= 1) {
			return *(this);
		}
		const auto& lhs = spaces.front();
		const auto& rhs = spaces.back();
		lhs->and(*rhs);
		return (*this);
	}

	BitSpaceTransformCommand move(const Math::Vector3d<float>& vector) {
		for (auto& b : spaces) {
			b->move(vector);
		}
		return (*this);
	}

	//Math::ScalarSpace3dSPtr<float> getSelected() { return  }

	Math::BitSpace3dSPtrList<float> getSpaces() const { return spaces; }

	bool isEmpty() const { return spaces.empty(); }

private:
	Math::BitSpace3dSPtrList<float> spaces;
};
	}
}

#endif