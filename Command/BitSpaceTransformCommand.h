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
		selecteds.push_back(space);
		return (*this);
	}

	BitSpaceTransformCommand& remove(const Math::BitSpace3dSPtr<float>& space) {
		selecteds.remove(space);
		return (*this);
	}

	BitSpaceTransformCommand& clear() {
		selecteds.clear();
		return (*this);
	}

	BitSpaceTransformCommand& not() {
		for (auto& b : selecteds) {
			b->not();
		}
		return (*this);
	}

	BitSpaceTransformCommand& and() {
		if (selecteds.size() <= 1) {
			return *(this);
		}
		const auto& lhs = selecteds.front();
		const auto& rhs = selecteds.back();
		lhs->and(*rhs);
		return (*this);
	}

	BitSpaceTransformCommand move(const Math::Vector3d<float>& vector) {
		for (auto& b : selecteds) {
			b->move(vector);
		}
		return (*this);
	}

	//Math::ScalarSpace3dSPtr<float> getSelected() { return  }

	bool isEmpty() const { return selecteds.empty(); }

private:
	Math::BitSpace3dSPtrList<float> selecteds;
};
	}
}

#endif