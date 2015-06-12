#ifndef __CRYSTAL_COMMAND_SCALAR_SPACE_FACTORY_H__
#define __CRYSTAL_COMMAND_SCALAR_SPACE_FACTORY_H__

#include "../Math/ScalarSpace.h"
#include "MainConfig.h"

#include <map>
#include <memory>

namespace Crystal{
	namespace Command {

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

template<typename T>
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

	ScalarSpaceId<T> create(const GridConfig& config)
	{
		Math::Grid3d<T> grid( std::get<0>(config), std::get<1>(config), std::get<2>( config));
		Math::ScalarSpace3dSPtr<T> ss(new Math::ScalarSpace3d<T>( std::get<3>(config), grid));
		//ss->add( Math::Metaball<float>( Math::Vector3d<float>(0.5, 0.5, 0.5), 0.5) );
		return add(ss);
	}

	ScalarSpaceIdList<T> getSpaces() const { return spaces; }

	Math::ScalarSpace3dSPtr<T> find(const unsigned int id) {
		for (const auto& s: spaces) {
			if (s.getId() == id) {
				return s.getScalarSpace();
			}
		}
		return nullptr;
	}


private:
	ScalarSpaceIdList<T> spaces;
	unsigned int nextId;

	ScalarSpaceId<T> add(const Math::ScalarSpace3dSPtr<T>& ss) {
		spaces.push_back( ScalarSpaceId<float>( nextId++, ss) );
		return spaces.back();
	}


};

template<typename T>
using ScalarSpaceFactorySPtr = std::shared_ptr < ScalarSpaceFactory<T> > ;

	}
}

#endif