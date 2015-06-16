#ifndef __CRYSTAL_COMMAND_MODEL_BASE_H__
#define __CRYSTAL_COMMAND_MODEL_BASE_H__

namespace Crystal {
	namespace Command {

class ModelBase {
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