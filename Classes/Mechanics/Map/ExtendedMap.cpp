#include "ExtendedMap.h"
#include "ExtendedMapInfo.h"
#include "../Entities/Fleet.h"

using namespace HexGame;

ExtendedMap::ExtendedMap()
{

}


ExtendedMap::~ExtendedMap()
{

}

ExtendedMap * HexGame::ExtendedMap::create(const std::string& mapFile)
{
	ExtendedMap *ret = new (std::nothrow) ExtendedMap();
	if (ret->initWithTMXFile(mapFile))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool ExtendedMap::initWithTMXFile(const std::string& mapFile)
{
	CCASSERT(mapFile.size()>0, "TMXTiledMap: tmx file should not be empty");

	setContentSize(Size::ZERO);

	ExtendedMapInfo *mapInfo = ExtendedMapInfo::create(mapFile, this);

	if (!mapInfo)
	{
		return false;
	}
	//CCASSERT(!mapInfo->getTilesets().empty(), "TMXTiledMap: Map not found. Please check the filename.");
	buildWithMapInfo(mapInfo);

	return true;
}

void ExtendedMap::buildWithMapInfo(ExtendedMapInfo* mapInfo)
{
}

void HexGame::ExtendedMap::addFleet(Fleet * fleet)
{
	m_vFleets.pushBack(fleet);
}
