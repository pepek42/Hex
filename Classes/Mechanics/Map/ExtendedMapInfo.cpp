#include "../Entities/Fleet.h"
#include "ExtendedMapInfo.h"
#include "CCFileUtils.h"
#include "CCSAXParser.h"
#include "ExtendedMap.h"

using namespace cocos2d;
using namespace HexGame;

ExtendedMapInfo::ExtendedMapInfo()
	: m_sCurrentString("")
	, m_pExtendedMap(nullptr)
{

}


ExtendedMapInfo::~ExtendedMapInfo()
{

}

ExtendedMapInfo* ExtendedMapInfo::create(const std::string& mapFile, ExtendedMap* extendedMap)
{
	ExtendedMapInfo *ret = new (std::nothrow) ExtendedMapInfo();
	ret->setExtendedMap(extendedMap);
	if (ret->initWithTMXFile(mapFile))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool ExtendedMapInfo::initWithTMXFile(const std::string& mapFile)
{
	return parseXMLFile(FileUtils::getInstance()->fullPathForFilename(mapFile).c_str());
}

bool ExtendedMapInfo::parseXMLFile(const std::string& xmlFilename)
{
	SAXParser parser;

	if (false == parser.init("UTF-8"))
	{
		return false;
	}

	parser.setDelegator(this);

	return parser.parse(FileUtils::getInstance()->fullPathForFilename(xmlFilename).c_str());
}

void ExtendedMapInfo::setExtendedMap(ExtendedMap* extendedMap)
{
	m_pExtendedMap = extendedMap;
}

// the XML parser calls here with all the elements
void ExtendedMapInfo::startElement(void *ctx, const char *name, const char **atts)
{
	CC_UNUSED_PARAM(ctx);
	ExtendedMapInfo *tmxMapInfo = this;
	std::string elementName = name;
	ValueMap attributeDict;
	if (atts && atts[0])
	{
		for (int i = 0; atts[i]; i += 2)
		{
			std::string key = atts[i];
			std::string value = atts[i + 1];
			attributeDict.insert(std::make_pair(key, Value(value)));
		}
	}
	if (elementName == "fleet")
	{
		m_pExtendedMap->addFleet(new Fleet(attributeDict["strength"].asFloat(), attributeDict["positionX"].asInt(),
			attributeDict["positionY"].asInt(), attributeDict["canMove"].asBool(), attributeDict["playerID"].asInt()));
	}
}

void ExtendedMapInfo::endElement(void *ctx, const char *name)
{
	CC_UNUSED_PARAM(ctx);
	ExtendedMapInfo *tmxMapInfo = this;
	std::string elementName = name;

	//if (elementName == "data")
	//{
	//}
}

void ExtendedMapInfo::textHandler(void *ctx, const char *ch, int len)
{
	//CC_UNUSED_PARAM(ctx);
	//ExtendedMapInfo *tmxMapInfo = this;
	//std::string text(ch, 0, len);

	//if (tmxMapInfo->isStoringCharacters())
	//{
	//	std::string currentString = tmxMapInfo->getCurrentString();
	//	currentString += text;
	//	tmxMapInfo->setCurrentString(currentString.c_str());
	//}
}