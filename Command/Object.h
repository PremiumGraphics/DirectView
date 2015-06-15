#ifndef __CRYSTAL_COMMAND_OBJECT_H__
#define __CRYSTAL_COMMAND_OBJECT_H__

namespace Crystal {
	namespace Command {

template<typename T>
class Object {
public:
	Object(const unsigned int id) :
		id(id)
	{}

	virtual ~Object(){}

	unsigned int getId() const { return id; }

private:
	unsigned int id;
};

	}
}

#endif