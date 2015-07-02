#ifndef __CRYSTAL_UI_BONE_COMMAND_H__
#define __CRYSTAL_UI_BONE_COMMAND_H__

#include "../Graphics/Bone.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace UI {

class BoneCommand : private UnCopyable
{
public:

	void create(const Math::Vector3d<float>& pos) {
		bones.push_back(std::make_shared<Graphics::Bone>());
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