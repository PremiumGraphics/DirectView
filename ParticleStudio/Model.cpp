#include "stdafx.h"

#include "../Graphics/Vertex.h"
#include "../Graphics/Face.h"
#include "Model.h"

using namespace Crystal::Graphics;
using namespace Crystal::CG;

void Model::setSelectedVertex(const unsigned int id)
{
	if (id >= 0 && id < getVertices().size()) {
		const VertexSPtrVector& vs = getVertices();
		const VertexSPtr& v = vs[id];
		this->selectedVertex.clear();
		this->selectedVertex.push_back(v);
	}
}

void Model::setSelectedFace(const unsigned int id)
{
	if (id >= 0 && id < getFaces().size()) {
		const FaceSPtrVector& faces = getFaces();
		const FaceSPtr& f = faces[id];
		this->selectedFace.clear();
		this->selectedFace.push_back(f);
	}
}
