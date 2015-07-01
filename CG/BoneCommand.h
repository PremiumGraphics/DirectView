#ifndef __CRYSTAL_UI_BONE_COMMAND_H__
#define __CRYSTAL_UI_BONE_COMMAND_H__

#include "../Graphics/Bone.h"

namespace Crystal {
	namespace UI {

class BoneCommand
{
public:

	void create() {
		bones.push_back(std::make_shared<Graphics::Bone<float>>());
	}

	Graphics::BoneSPtr<float> getSelectedBone() const { return bones.back(); }

	Graphics::BoneSPtrList<float> getBones() const { return bones; }

	Math::Vector3dVector<float> toPositions() {
		return bones.back()->getLine().toPositions(10);
	}

private:

	Graphics::BoneSPtrList<float> bones;

};
	}
}

#endif