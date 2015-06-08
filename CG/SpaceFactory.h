#ifndef __CRYSTAL_CGS_SPACE_FACTORY__
#define __CRYSTAL_CGS_SPACE_FACTORY__

#include "../Math/ScalarSpace.h"
#include "../Math/BitSpace.h"
#include <memory>
#include <map>


namespace Crystal {
	namespace CG {

template<typename T>
using ScalarSpace3dSPtr = std::shared_ptr < Math::ScalarSpace3d<T> >;

template<typename T>
using ScalarSpace3dSPtrList = std::list < ScalarSpace3dSPtr<T> >;

template<typename T>
using BitSpace3dSPtr = std::shared_ptr < Math::BitSpace3d<T> >;

template<typename T>
using BitSpace3dSPtrList = std::list < BitSpace3dSPtr<T> >;

template<typename T>
using BitSpaceIdMap = std::map< BitSpace3dSPtr<T>, unsigned int >;


class SpaceFactory
{
public:
	void addBitSpace(const BitSpace3dSPtr<float>& bs) { bitSpaces.push_back(bs); }

	BitSpace3dSPtrList<float> getBitSpaces() const { return bitSpaces; }

	void addScalarSpace(const ScalarSpace3dSPtr<float>& ss) { scalarSpaces.push_back(ss); }

	ScalarSpace3dSPtrList<float> getScalarSpaces() const { return scalarSpaces; }

	void clear() {
		bitSpaces.clear();
	}

private:
	BitSpace3dSPtrList<float> bitSpaces;
	ScalarSpace3dSPtrList<float> scalarSpaces;
	unsigned int nextSpaceId;
};

	}
}

#endif