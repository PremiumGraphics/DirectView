#include "CGBFile.h"
#include "../ThirdParty/tinyxml2-master/tinyxml2.cpp"

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace tinyxml2;

bool CGBFile::save(const std::string& filename, const Volume3d<float>& volume)
{
	auto xml = buildXML(volume);
	xml->SaveFile(filename.c_str());
	return true;//saveImages(directory, filename);
}

std::shared_ptr<XMLDocument> CGBFile::buildXML(const Volume3d<float>& volume)
{
	std::shared_ptr<XMLDocument> xml = std::make_shared< XMLDocument >();
	XMLDeclaration* decl = xml->NewDeclaration();
	xml->InsertEndChild(decl);
	XMLNode* root = xml->NewElement("root");
	xml->InsertEndChild(root);

	{
		XMLElement* size = xml->NewElement("res");

		size->SetAttribute("x", volume.getResolutions()[0]);
		size->SetAttribute("y", volume.getResolutions()[1]);
		size->SetAttribute("z", volume.getResolutions()[2]);

		root->InsertEndChild(size);
	}

	{
		XMLElement* origin = xml->NewElement("origin");

		const auto& start = volume.getStart();
		origin->SetAttribute("x", start.getX());
		origin->SetAttribute("y", start.getY());
		origin->SetAttribute("z", start.getZ());

		root->InsertEndChild(origin);
	}
	
	return xml;

}
