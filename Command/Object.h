#ifndef __CRYSTAL_COMMAND_OBJECT_H__
#define __CRYSTAL_COMMAND_OBJECT_H__

#include "../Math/Vector.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Model {

class Object {
public:
	enum class Type {
		NullType = 0,
		VOLUME = 1,
		Metaball = 2,
		Light = 3,
		Polygon = 4,
		Camera = 5,
		PointCloud = 6,
	};

	explicit Object(const unsigned int id) :
		id(id),
		selected(false)
	{}

	virtual ~Object(){};

	virtual Type getType() const = 0;

	unsigned int getId() const { return id; }

	bool isSelected() const { return selected; }

	void setSelect() { selected = true; }

	void setUnSelect() { selected = false; }

	void changeSelected() { selected = !selected; }

	virtual void move(const Math::Vector3d<float>& vector){};

	virtual void scale(const Math::Vector3d<float>& vector){};

	virtual void rotate(const Math::Vector3d<float>& center, const Math::Vector3d<float>& angle){};

private:
	unsigned int id;
	bool selected;
};

	}
}

#endif