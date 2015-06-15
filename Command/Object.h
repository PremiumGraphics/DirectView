#ifndef __CRYSTAL_COMMAND_OBJECT_H__
#define __CRYSTAL_COMMAND_OBJECT_H__

#include "../Math/Vector.h"

namespace Crystal {
	namespace Command {

class Object {
public:
	enum class Type {
		NullType = -1,
		ScalarSpace = 0,
		Metaball = 1,
		Light = 2,
		Polygon = 3,
		Camera = 4,
	};

	explicit Object(const unsigned int id) :
		id(id),
		visible(true),
		selected(false)
	{}

	virtual ~Object(){};

	virtual Type getType() const = 0;

	unsigned int getId() const { return id; }

	bool isVisible() const { return visible; }

	bool isInvisible() const { return !isVisible(); }

	void setVisible() { visible = true; }

	void setInvisible() { visible = false; }

	bool isSelected() const { return selected; }

	void setSelect() { selected = true; }

	void setUnselect() { selected = false; }

	std::string getName() const { return name; }

	virtual void move(const Math::Vector3d<float>& vector){};

	//ScalarSpaceTransformCommand& move(const Math::Vector3d<float>& vector) {
	//	for (auto& b : spaces) {
	//		b->move(vector);
	//	}
	//	return (*this);
	//}

	//ScalarSpaceTransformCommand& scale(const Math::Vector3d<float>& scale) {
	//	for (auto& b : spaces) {
	//		b->scale(scale);
	//	}
	//	return (*this);
	//}

	//ScalarSpaceTransformCommand& add(const Math::ScalarSpace3dSPtr<T>& ss) {
	//	spaces.push_back(ss);
	//	return (*this);
	//}


private:
	unsigned int id;
	bool visible;
	bool selected;
	std::string name;
};

class NullObject : public Object{
	NullObject() :
		Object(-1)
	{}

	Type getType() const { return Type::NullType; }


	~NullObject(){}
};
	}
}

#endif