#ifndef __CRYSTAL_UI_BONE_COMMAND_H__
#define __CRYSTAL_UI_BONE_COMMAND_H__

#include "../Graphics/Bone.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace UI {

class BoneCommand : private UnCopyable
{
public:
	BoneCommand() = default;

	~BoneCommand() = default;

	void clear() {
		bones.clear();
	}

	void create(const Math::Vector3d<float>& start, const Math::Vector3d<float>& end) {
		bones.push_back(std::make_shared<Graphics::Bone>(start, end));
	}

	Graphics::BoneSPtr getSelectedBone() const { return bones.back(); }

	Graphics::BoneSPtrList getBones() const { return bones; }

	Math::Vector3dVector<float> toPositions() {
		return bones.back()->getLine().toPositions(10);
	}

private:
	Graphics::BoneSPtrList bones;

};
	}
}

#endif