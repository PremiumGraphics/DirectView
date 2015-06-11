#ifndef __CRYSTAL_COMMAND_SCALAR_SPACE_FACTORY_H__
#define __CRYSTAL_COMMAND_SCALAR_SPACE_FACTORY_H__

#include "../Math/ScalarSpace.h"
#include "MainConfig.h"

#include <map>
#include <memory>

namespace Crystal{
	namespace Command {

template<typename T>
using ScalarSpaceIdMap = std::map < Math::ScalarSpace3dSPtr<T>, unsigned int >;

template<typename T>
using IdScalarSpaceMap = std::map < unsigned int, Math::ScalarSpace3dSPtr<T> >;

/*
class FactoryBase {
public:
	FactoryBase() :
		nextId(0)
	{}

	virtual ~FactoryBase() = default;

	unsigned int nextId;
};
*/

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

	Math::ScalarSpace3dSPtr<float> create(const GridConfig& config)
	{
		Math::Grid3d<float> grid(config.getResx(), config.getResy(), config.getResz());
		Math::ScalarSpace3dSPtr<float> ss(new Math::ScalarSpace3d<float>(config.getSpace(), grid));
		//ss->add( Math::Metaball<float>( Math::Vector3d<float>(0.5, 0.5, 0.5), 0.5) );
		add(ss);
		return ss;
	}

	Math::ScalarSpace3dSPtrList<float> getScalarSpaces() const { return spaces; }

	Math::Vector3dVector<float> toCenterPositions() const {
		Math::Vector3dVector<float> positions;
		for (const auto& s : spaces) {
			const auto& ps = s->toCenterPositions();
			positions.insert(positions.end(), ps.begin(), ps.end());
		}
		return positions;
		/*
		for (const auto s : spaces) {
			s->toCenterPosition();
		}
		*/
	}

private:
	Math::ScalarSpace3dSPtrList<float> spaces;
	ScalarSpaceIdMap<float> spaceIdMap;
	IdScalarSpaceMap<float> idSpaceMap;
	unsigned int nextId;

	void add(const Math::ScalarSpace3dSPtr<float>& ss) {
		spaces.push_back(ss);
		spaceIdMap[ss] = nextId;
		idSpaceMap[nextId] = ss;
		nextId++;
	}


};

using ScalarSpaceFactorySPtr = std::shared_ptr < ScalarSpaceFactory > ;

	}
}

#endif