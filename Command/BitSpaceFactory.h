#ifndef __CRYSTAL_COMMAND_BIT_SPACE_FACTORY__
#define __CRYSTAL_COMMAND_BIT_SPACE_FACTORY__

#include "../Math/BitSpace.h"
#include <memory>
#include <map>
#include <list>


namespace Crystal {
	namespace Command {


template<typename T>
using BitSpaceIdMap = std::map< Math::BitSpace3dSPtr<T>, unsigned int >;

template<typename T>
using IdBitSpacemap = std::map < unsigned int, Math::BitSpace3dSPtr<T> > ;


class BitSpaceFactory
{
public:
	BitSpaceFactory() :
		nextId(0)
	{}

	void clear() {
		bitSpaces.clear();
		nextId = 0;
	}


	Math::BitSpace3dSPtrList<float> getBitSpaces() const { return bitSpaces; }


	Math::BitSpace3dSPtr<float> createBox(const unsigned int resx, const unsigned int resy, const unsigned int resz) {
		Math::Space3d<float> space(Math::Vector3d<float>(0, 0, 0), Math::Vector3d<float>(1, 1, 1));

		Math::Bitmap3d bmp(resx, resy, resz);
		Math::BitSpace3dSPtr<float> bs(new Math::BitSpace3d<float>(space, bmp));
		bs->setBox();
		addBitSpace(bs);
		return bs;
	}

	Math::BitSpace3dSPtr<float> createSphere(const unsigned int resx, const unsigned int resy, const unsigned int resz) {
		Math::Space3d<float> space(Math::Vector3d<float>(0, 0, 0), Math::Vector3d<float>(1, 1, 1));

		Math::Bitmap3d bmp(20, 20, 20);
		Math::BitSpace3dSPtr<float> bs(new Math::BitSpace3d<float>(space, bmp));
		bs->setSphere();
		addBitSpace(bs);
		return bs;
	}

	Math::BitSpace3dSPtr<float> createCylinder(const unsigned int resx, const unsigned int resy, const unsigned int resz) {
		Math::Space3d<float> space(Math::Vector3d<float>(0, 0, 0), Math::Vector3d<float>(1, 1, 1));
		Math::Bitmap3d bmp(20, 20, 20);
		Math::BitSpace3dSPtr<float> bs(new Math::BitSpace3d<float>(space, bmp));
		bs->setBox();
		bs->not();
		addBitSpace(bs);

		return bs;
	}


	unsigned int getId(const Math::BitSpace3dSPtr<float>& bs) { return bitIdMap[bs]; }



private:
	Math::BitSpace3dSPtrList<float> bitSpaces;
	BitSpaceIdMap<float> bitIdMap;
	IdBitSpacemap<float> idBitMap;
	unsigned int nextId;

	void addBitSpace(const Math::BitSpace3dSPtr<float>& bs) {
		bitSpaces.push_back(bs);
		bitIdMap[bs] = nextId;
		idBitMap[nextId] = bs;
		nextId++;
	}


};


	}
}

#endif