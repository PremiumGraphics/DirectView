#ifndef __CRYSTAL_COMMAND_OBJECT_H__
#define __CRYSTAL_COMMAND_OBJECT_H__

namespace Crystal {
	namespace Command {

class Object {
public:
	enum class Type {
		ScalarSpace = 0,
		Metaball = 1,
		Light = 2,
		Polygon = 3,
	};


	Object(const unsigned int id) :
		id(id)
	{}

	virtual ~Object(){}

	unsigned int getId() const { return id; }

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
};

class NullObject : public Object{
	NullObject() :
		Object(-1)
	{}

	~NullObject(){}
};
	}
}

#endif