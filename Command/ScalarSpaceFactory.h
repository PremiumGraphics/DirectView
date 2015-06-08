#ifndef __CRYSTAL_COMMAND_SCALAR_SPACE_FACTORY_H__
#define __CRYSTAL_COMMAND_SCALAR_SPACE_FACTORY_H__

#include "../Math/ScalarSpace.h"

#include <map>


namespace Crystal{
	namespace Command {

template<typename T>
using ScalarSpaceIdMap = std::map < Math::ScalarSpace3dSPtr<T>, unsigned int >;

template<typename T>
using IdScalarSpaceMap = std::map < unsigned int, Math::ScalarSpace3dSPtr<T> >;


class ScalarSpaceFactory final
{
public:
	ScalarSpaceFactory() :
		nextId(0)
	{}

	void clear() {
		spaces.clear();
		nextId = 0;
	}

	void add(const Math::ScalarSpace3dSPtr<float>& ss) {
		spaces.push_back(ss);
		spaceIdMap[ss] = nextId;
		idSpaceMap[nextId] = ss;
		nextId++;
	}

	unsigned int getId(const Math::ScalarSpace3dSPtr<float>& ss) {
		if ( spaceIdMap.find(ss) == spaceIdMap.end()) {
			return -1;
		}
		return spaceIdMap[ss];
	}

	Math::ScalarSpace3dSPtr<float> getSpace(const unsigned int id) {
		if (idSpaceMap.find(id) == idSpaceMap.end()) {
			return nullptr;
		}
		return idSpaceMap[id];
	}

	Math::ScalarSpace3dSPtrList<float> getScalarSpaces() const { return spaces; }

private:
	Math::ScalarSpace3dSPtrList<float> spaces;
	ScalarSpaceIdMap<float> spaceIdMap;
	IdScalarSpaceMap<float> idSpaceMap;
	unsigned int nextId;

};

	}
}

#endif