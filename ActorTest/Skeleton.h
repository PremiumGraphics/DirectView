#ifndef __CRYSTAL_ACTOR_SKELETON_H__
#define __CRYSTAL_ACTOR_SKELETON_H__

#include "Bone.h"

#include <list>

namespace Crystal {
	namespace Actor {

template<typename T>
class Skeleton {
public:

	void move(const Math::Vector3d<T>& v) {
		for (auto& j : joints) {
			j->move(v);
		}
	}

	BoneSPtr<T> buildBone(const Math::Vector3d<T>& start, const Math::Vector3d<T>& end) {
		const auto& js = buildJoints({ start, end });
		const auto& b = createBone(js[0], js[1]);
		return b;
	}

	BoneSPtrList<T> buildBones(const Math::Vector3d<T>& start, const Math::Vector3d<T>& middle, const Math::Vector3d<T>& end) {
		const auto& js = buildJoints({ start, middle, end });
		const auto b1 = std::make_shared<Bone<T>>(js[0], js[1]);
		const auto b2 = std::make_shared<Bone<T>>(js[1], js[2]);
		return{ b1, b2 };
	}

	void insertJoint(const BoneSPtr<T>& targetBone, const Math::Vector3d<T>& jointPos) {
		const auto& end = targetBone->getEndPosition();
		targetBone->moveEnd(jointPos);
	}

	JointSPtrVector<T> buildJoints(const Math::Vector3dVector<T>& positions) {
		JointSPtrVector<T> js;
		for (const auto& p : positions) {
			js.push_back(buildJoint(p));
		}
		return js;
	}

	JointSPtr<T> buildJoint(const Math::Vector3d<T>& v) {
		const auto j = std::make_shared<Joint<T> >(v);
		joints.push_back(j);
		return j;
	}

	BoneSPtr<T> createBone(const JointSPtr<T>& j1, const JointSPtr<T>& j2) {
		const auto b = std::make_shared< Bone<T> >(j1, j2);
		bones.push_back(b);
		return b;
	}


	BoneSPtrList<T> getBones() const { return bones; }

	JointSPtrList<T> getJoints() const { return joints; }

private:
	BoneSPtrList<T> bones;
	JointSPtrList<T> joints;





};


	}
}

#endif