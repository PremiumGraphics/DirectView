#ifndef __CRYSTAL_COMMAND_OBJECT_H__
#define __CRYSTAL_COMMAND_OBJECT_H__

#include "../Math/Vector.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Command {

class Object {
public:
	enum class Type {
		NullType = -1,
		VOLUME = 0,
		Metaball = 1,
		Light = 2,
		Polygon = 3,
		Camera = 4,
		PointCloud = 5,
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

	virtual void scale(const Math::Vector3d<float>& vector){};

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

class ModelBase : private UnCopyable {
public:
	ModelBase() :
		nextId(0)
	{}

	virtual ~ModelBase(){};

	void clear() {
		nextId = 0;
	}

	unsigned int getNextId() { return nextId++; }

	virtual void remove(const unsigned int id) = 0;

private:
	unsigned int nextId;
};

	}
}

#endif