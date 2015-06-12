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

template<typename T>
class ScalarSpaceId
{
public:
	ScalarSpaceId(const unsigned int id, const Math::ScalarSpace3dSPtr<T>& ss) :
		id( id ),
		ss( ss )
	{}

	unsigned int getId() const { return id; }

	Math::ScalarSpace3dSPtr<T> getScalarSpace() const { return ss; }

private:
	unsigned int id;
	Math::ScalarSpace3dSPtr<T> ss;
};

template<typename T>
using ScalarSpaceIdList = std::list < ScalarSpaceId<T> > ;

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

	ScalarSpaceId<float> create(const GridConfig& config)
	{
		Math::Grid3d<float> grid( std::get<0>(config), std::get<1>(config), std::get<2>( config));
		Math::ScalarSpace3dSPtr<float> ss(new Math::ScalarSpace3d<float>( std::get<3>(config), grid));
		//ss->add( Math::Metaball<float>( Math::Vector3d<float>(0.5, 0.5, 0.5), 0.5) );
		return add(ss);
	}

	ScalarSpaceIdList<float> getScalarSpaces() const { return spaces; }

	//Math::Vector3dVector<float> toCenterPositions() const {
	//	Math::Vector3dVector<float> positions;
	//	for (const auto& s : spaces) {
	//		const auto& ps = s->toCenterPositions();
	//		positions.insert(positions.end(), ps.begin(), ps.end());
	//	}
	//	return positions;
	//	/*
	//	for (const auto s : spaces) {
	//		s->toCenterPosition();
	//	}
	//	*/
	//}

private:
	ScalarSpaceIdList<float> spaces;
	unsigned int nextId;

	ScalarSpaceId<float> add(const Math::ScalarSpace3dSPtr<float>& ss) {
		spaces.push_back( ScalarSpaceId<float>( nextId++, ss) );
		return spaces.back();
	}


};

using ScalarSpaceFactorySPtr = std::shared_ptr < ScalarSpaceFactory > ;

	}
}

#endif