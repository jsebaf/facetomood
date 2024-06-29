/*
 * dom-support.h
 *
 *  Created on: 21 de oct. de 2015
 *      Author: jseba
 */

#ifndef DOM_SUPPORT_H_
#define DOM_SUPPORT_H_

#include <tinyxml2.h>

#include <vector>
#include <string>

namespace xml = tinyxml2;

namespace ds {

class NodeListByName : public xml::XMLVisitor {
public:
	std::vector<xml::XMLElement *> nodes;

	NodeListByName(std::string name) : name(name) {};

	virtual bool VisitEnter (const xml::XMLElement & element, const xml::XMLAttribute *) {

		std::string element_name(element.Name());

		if(element_name == name)
			nodes.push_back(const_cast<xml::XMLElement *>(&element));

		return true;
	}

private:
	std::string name;
};

class DomSupport {
public:
	DomSupport();
	virtual ~DomSupport();

	xml::XMLDocument * loadDocument(const std::string& fileName);

	xml::XMLDocument * loadDocumentFromString(const std::string& xml);

	xml::XMLDocument * newDocument(const std::string& rootName);

	void writeToFile(xml::XMLDocument * document, const std::string& fileName);

	std::vector<xml::XMLElement *> getElementsByTagName(xml::XMLNode * document, const std::string& tagName);

private:
	std::vector<xml::XMLDocument *> ownedDocuments;
};

} /* namespace ds */

#endif /* DOM_SUPPORT_H_ */
