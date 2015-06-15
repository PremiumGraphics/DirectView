#ifndef __CRYSTAL_COMMAND_FACTORY_H__
#define __CRYSTAL_COMMAND_FACTORY_H__

namespace Crystal {
	namespace Command {

class FactoryBase {
public:
	FactoryBase() :
		nextId(0)
	{}

	virtual ~FactoryBase(){};

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