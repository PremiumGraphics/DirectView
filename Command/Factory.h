#ifndef __CRYSTAL_COMMAND_OBJECT_FACTORY_H__
#define __CRYSTAL_COMMAND_OBJECT_FACTORY_H__

namespace Crystal {
	namespace Command {

class ObjectFactory {
public:
	ObjectFactory() :
		nextId(0)
	{}

	virtual ~ObjectFactory(){};

	void clear() {
		nextId = 0;
	}

	unsigned int getNextId() { return nextId++; }

private:
	unsigned int nextId;
};

	}
}

#endif