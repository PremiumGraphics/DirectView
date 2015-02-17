#include "AVSCell.h"

using namespace Crystal::IO;

AVSCell::Type AVSCell::toAVSType(const std::string& str)
{
	if( str == "point" ) {
		return Type::Point;
	}
	else if( str == "line") {
		return Type::Line;
	}
	else if( str == "tri") {
		return Type::Tri;
	}
	else if( str == "quad") {
		return Type::Quad;
	}
	else if( str == "tet") {
		return Type::Tet;
	}
	else if( str == "pyr" ) {
		return Type::Pyr;
	}
	else if( str == "prism") {
		return Type::Prism;
	}
	else if( str == "hex") {
		return Type::Hex;
	}
	else {
		assert( false );
		return Type::None;
	}
};

AVSCell* AVSCell::create(const Type& type, const VertexIndices& indices)
{
	switch( type )
	{
	case Type::Point :
		{
			return new AVSPoint(indices);
		}
	case Type::Line :
		{
			return new AVSLine(indices);
		}
	case Type::Tri :
		{
			return new AVSTri(indices);
		}
	case Type::Quad :
		{
			return new AVSQuad(indices);
		}
	case Type::Tet :
		{
			return new AVSTet(indices);
		}
	case Type::Pyr :
		{
			return new AVSPyr(indices);
		}
	case Type::Prism :
		{
			return new AVSPrism(indices);
		}
	case Type::Hex :
		{
			return new AVSHex(indices);
		}
	default :
		{
			assert( false );
			return nullptr;
		}
	}
}