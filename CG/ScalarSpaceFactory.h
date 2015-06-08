#ifndef __CRYSTAL_CGS_SCALAR_SPACE_FACTORY_H__
#define __CRYSTAL_CGS_SCALAR_SPACE_FACTORY_H__

#include "../Math/ScalarSpace.h"

#include <map>


namespace Crystal{
	namespace Command {

template<typename T>
using ScalarSpaceIdMap = std::map < Math::ScalarSpace3dSPtr<T>, unsigned int >;

template<typename T>
using IdScalarSpaceMap = std::map < unsigned int, Math::ScalarSpace3dSPtr<T> >;


class ScalarSpaceFactory
{
public:
	ScalarSpaceFactory() :
		nextId(0)
	{}

	void clear() {
		scalarSpaces.clear();
		nextId = 0;
	}

	void addScalarSpace(const Math::ScalarSpace3dSPtr<float>& ss) {
		scalarSpaces.push_back(ss);
		scalarIdMap[ss] = nextId;
		idScalarMap[nextId] = ss;
		nextId++;
	}

	unsigned int getId(const Math::ScalarSpace3dSPtr<float>& ss) { return scalarIdMap[ss]; }

	Math::ScalarSpace3dSPtr<float> getScalarSpace(const unsigned int id) { return idScalarMap[id]; }

	Math::ScalarSpace3dSPtrList<float> getScalarSpaces() const { return scalarSpaces; }


private:
	Math::ScalarSpace3dSPtrList<float> scalarSpaces;
	ScalarSpaceIdMap<float> scalarIdMap;
	IdScalarSpaceMap<float> idScalarMap;
	unsigned int nextId;

};

	}
}

#endif