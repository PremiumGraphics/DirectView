#include "CGSFile.h"

#include "tinyxml2.h"

#include "XMLIOHelper.h"

using namespace tinyxml2;

//using namespace Crystal::Graphics;
using namespace Crystal::CG;

bool CGSFile::save( const std::string& filename )
{
	///*

	//XMLDocument doc;
	//XMLElement* root = doc.NewElement("root");
	//doc.InsertEndChild( root );

	//const PolygonList& polygons = model->getPolygonModel()->getPolygons();
	//XMLElement* polygonElem = doc.NewElement("Polygon");
	//for( Graphics::Polygon* p : polygons ) {
	//	polygonElem->SetAttribute( "ID", p->getId() );
	//	polygonElem->SetAttribute( "Selected", p->isSelected );

	//	const VertexVector& vertices = p->getVertices();
	//	XMLElement* vertexElem = doc.NewElement( "Vertex" );
	//	for( Vertex* v : vertices ) {
	//		XMLElement* posElem = doc.NewElement("Pos");
	//		XMLIOHelper::save( posElem, v->position );
	//		vertexElem->InsertEndChild( posElem );

	//		XMLElement* normalElem = doc.NewElement("Normal");
	//		XMLIOHelper::save( normalElem, v->normal );
	//		vertexElem->InsertEndChild( normalElem );

	//		XMLElement* texCoordElem = doc.NewElement("TexCoord");
	//		XMLIOHelper::save( texCoordElem, v->getTextureCoord() );
	//		vertexElem->InsertEndChild( texCoordElem );
	//	}
	//	polygonElem->InsertEndChild( vertexElem );

	//	const FaceVector& faces = p->getFaces();
	//	XMLElement* faceElem = doc.NewElement( "Face" );
	//	for( Face* f: faces ) {
	//		const VertexVector& vertices = f->getVertices();
	//		XMLElement* idsElem = doc.NewElement( "VertexIds" );
	//		for( Vertex* v: vertices ) {
	//			idsElem->SetAttribute( "ID", v->getId() );
	//		}
	//		faceElem->InsertEndChild( idsElem );
	//	}
	//	polygonElem->InsertEndChild( faceElem );
	//}
	//root->InsertEndChild( polygonElem );

	//const MaterialList& materials = model->getMaterialModel()->getMaterials();
	//XMLElement* materialsElem = doc.NewElement("Materials");
	//for( Material* m : materials ) {
	//	XMLElement* materialElem = doc.NewElement("Material");
	//	materialElem->SetAttribute( "ID", m->getId() );

	//	XMLElement* ambientElem = doc.NewElement("Ambient");
	//	XMLIOHelper::save( ambientElem, m->getAmbient() );
	//	materialElem->InsertEndChild( ambientElem );

	//	XMLElement* diffuseElem = doc.NewElement("Diffuse");
	//	XMLIOHelper::save( diffuseElem, m->getDiffuse() );
	//	materialElem->InsertEndChild( diffuseElem );

	//	XMLElement* specularElem = doc.NewElement("Specular");
	//	XMLIOHelper::save( specularElem, m->getSpecular() );
	//	materialElem->InsertEndChild( specularElem );

	//	/*
	//	XMLElement* ambientTexElem = doc.NewElement("AmbientTex");
	//	ambientTexElem->SetText( m->texture.getAmbientFileName().c_str() );
	//	materialElem->InsertEndChild( ambientTexElem );

	//	XMLElement* diffuseTexElem = doc.NewElement("DiffuseTex");
	//	diffuseTexElem->SetText( m->texture.getDiffuseFileName().c_str() );
	//	materialElem->InsertEndChild( diffuseTexElem );

	//	XMLElement* specularTexElem = doc.NewElement("SpecularTex");
	//	specularTexElem->SetText( m->texture.getSpecularFileName().c_str() );
	//	materialElem->InsertEndChild( specularTexElem );

	//	XMLElement* alphaTexElem = doc.NewElement("AlphaTex");
	//	alphaTexElem->SetText( m->texture.getAlphaFileName().c_str() );
	//	materialElem->InsertEndChild( alphaTexElem );

	//	//XMLElement* normalTexElem = doc.NewElement("NormalTex");
	//	materialsElem->InsertEndChild( materialElem );
	//}
	//root->InsertEndChild( materialsElem);

	//const LightList& lights = model->getLightModel()->getLights();
	//XMLElement* lightsElem = doc.NewElement("Lights");
	//for( Light* l : lights ) {
	//	XMLElement* lightElem = doc.NewElement("Light");
	//	lightElem->SetAttribute( "ID", l->getId() );
	//	lightElem->SetAttribute( "Selected", l->isSelected );

	//	XMLElement* posElem = doc.NewElement("Pos");
	//	XMLIOHelper::save( posElem, l->pos );
	//	lightElem->InsertEndChild( posElem );

	//	XMLElement* ambientElem = doc.NewElement("Ambient");
	//	XMLIOHelper::save( ambientElem, l->getAmbient() );
	//	lightElem->InsertEndChild( ambientElem );

	//	XMLElement* diffuseElem = doc.NewElement("Diffuse");
	//	XMLIOHelper::save( diffuseElem, l->getDiffuse() );
	//	lightElem->InsertEndChild( diffuseElem );

	//	XMLElement* specularElem = doc.NewElement("Specular");
	//	XMLIOHelper::save( specularElem, l->getSpecular() );
	//	lightElem->InsertEndChild( specularElem );

	//	lightsElem->InsertEndChild( lightElem );
	//}
	//root->InsertEndChild( lightsElem );

	//Camera<float>* camera = model->getCamera();
	//XMLElement* cameraElem = doc.NewElement("camera");
	//{
	//	XMLElement* posElem = doc.NewElement("pos");
	//	XMLIOHelper::save( posElem, camera->getPos() );
	//	cameraElem->InsertEndChild( posElem );

	//	XMLElement* nearElem = doc.NewElement("near");
	//	nearElem->SetAttribute( "near", camera->getNear() );
	//	cameraElem->InsertEndChild( nearElem );

	//	XMLElement* farElem = doc.NewElement("far");
	//	farElem->SetAttribute( "far", camera->getFar() );
	//	cameraElem->InsertEndChild( farElem );

	//	XMLElement* angleElem = doc.NewElement("angle");
	//	XMLIOHelper::save( angleElem, camera->getAngle() );
	//	cameraElem->InsertEndChild( angleElem );
	//}
	//root->InsertEndChild( cameraElem );


	//const XMLError error = doc.SaveFile( filename.c_str() );
	//return ( error == XML_NO_ERROR );
	return false;
}