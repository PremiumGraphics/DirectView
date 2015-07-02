#ifndef __CRYSTAL_GRAPHICS_BONE_H__
#define __CRYSTAL_GRAPHICS_BONE_H__

#include "../Math/Vector.h"
#include "../Math/Line.h"

#include <memory>
#include <list>

namespace Crystal {
	namespace Graphics {

class Bone
{
public:
	Bone() = default;

	Bone(const Math::Vector3d<float>& start, const Math::Vector3d<float>& end) :
		start( start ),
		end( end )
	{
	}

	Math::Line3d<float> getLine() const {
		return Math::Line3d<float>(start, end);
	}

	/*
	Math::Vector3dVector<float> getPosition(const float param) const {
		return getLine().getPosition(param);
	}
	*/

	void move(const Math::Vector3d<float>& v) {
		start += v;
		end += v;
	}

	void moveEnd(const Math::Vector3d<float>& v) {
		end += v;
	}

private:
	Math::Vector3d<float> start;
	Math::Vector3d<float> end;
};

using BoneSPtr = std::shared_ptr < Bone > ;

using BoneSPtrList = std::list < BoneSPtr > ;
	}
}

#endif