#include "ExtendedMap.h"
#include "ExtendedMapInfo.h"
#include "../Entities/Fleet.h"
#include "Scenes\Scenario.h"
#include "../Player.h"

using namespace HexGame;

ExtendedMap::ExtendedMap()
	: CCTMXTiledMap()
	, m_selectedFleet(nullptr)
	, m_parentScene(nullptr)
{

}


ExtendedMap::~ExtendedMap()
{
	for (auto it = m_players.begin(); it != m_players.end(); ++it)
	{
		if ((*it).second != nullptr)
		{
			delete (*it).second;
			(*it).second = nullptr;
		}
	}
	m_players.clear();
}

ExtendedMap * HexGame::ExtendedMap::create(const std::string& tmxFile, const std::string& mapFile, Scenario * _parentScenario)
{
	ExtendedMap *ret = new (std::nothrow) ExtendedMap();
	if (ret->initWithTMXFile(tmxFile) && ret->initWithMapFile(mapFile))
	{
		ret->autorelease();
		ret->m_parentScene = _parentScenario;
		ret->updateMap();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool ExtendedMap::initWithMapFile(const std::string& mapFile)
{
	CCASSERT(mapFile.size()>0, "TMXTiledMap: tmx file should not be empty");

	setContentSize(Size::ZERO);

	m_tileLayer = getLayer("Hexes");

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

void ExtendedMap::addFleet(Fleet * fleet)
{
	m_vFleets.pushBack(fleet);
	addChild(fleet);
	updateMap();
}

void ExtendedMap::actionAt(Vec2 mouseClickPosition)
{
	Size layerSize = m_tileLayer->getLayerSize();

	for (auto it = m_vFleets.begin(); it != m_vFleets.end(); ++it)
	{
		Vec2 basePosition = (*it)->getPosition();
		Size spriteSize = (*it)->getContentSize();
		if (basePosition.x < mouseClickPosition.x && basePosition.y < mouseClickPosition.y)
		{
			if (mouseClickPosition.x < (basePosition.x + spriteSize.width) && mouseClickPosition.y < (basePosition.y + spriteSize.height))
			{
				if (m_selectedFleet == *it) {
					m_selectedFleet = nullptr;
				}
				else {
					m_selectedFleet = *it;
				}
				return;
			}
		}
	}

	if (m_selectedFleet == nullptr || !m_selectedFleet->getCanMove())
	{
		m_selectedFleet = nullptr;
		return;
	}
	for (int x = 0; x < layerSize.width; ++x)
	{
		for (int y = 0; y < layerSize.height; ++y)
		{
			Sprite* tile = m_tileLayer->tileAt(Vec2(x, y));
			Vec2 spriteCenter = Vec2(tile->getPositionX() + _tileSize.width / 2, tile->getPositionY() + _tileSize.height / 2);
			// michal ppk to do tile detection
			Vec2 diff = spriteCenter - ccp(mouseClickPosition.x, mouseClickPosition.y);
			if (diff.length() < _tileSize.height / 2)
			{
				m_selectedFleet->setPositionInTiles(x, y);
				m_selectedFleet->setCanMove(false);
				m_selectedFleet = nullptr;
				updateMap();
				return;
			}
		}
	}
}

void ExtendedMap::setPlayerCount(int _playerCount)
{
	m_playerCount = _playerCount;
}
void ExtendedMap::setCurrentPlayerTurnID(int _currentPlayerTurnID)
{
	m_currentPlayerTurnID = _currentPlayerTurnID;
}

int ExtendedMap::getPlayerCount()
{
	return m_playerCount;
}
int ExtendedMap::getCurrentPlayerTurnID()
{
	return m_currentPlayerTurnID;
}

void ExtendedMap::updateMap()
{
	Size layerSize = m_tileLayer->getLayerSize();

	for (auto it = m_vFleets.begin(); it != m_vFleets.end(); ++it)
	{
		int id = (*it)->getPlayerID();
		Player* player = (*m_players.find(id)).second;
		Size spriteSize = (*it)->getContentSize();
		Vec2 positionInHex = (*it)->getPositionInHexes();
		Sprite* tile = m_tileLayer->getTileAt(positionInHex);
		float swap = (id == m_currentPlayerTurnID ? -spriteSize.width : 0);
		(*it)->setPosition(tile->getPositionX() + _tileSize.width / 2 + swap, tile->getPositionY() + _tileSize.height / 2);
		(*it)->setColor(player->getColor());

	}
}

void ExtendedMap::addPlayer(Player* _player)
{
	int id = _player->getID();
	CCASSERT(1 <= id && id <= m_playerCount, "Player ID exiding player count");
	CCASSERT(m_players.find(id) == m_players.end(), std::string("Player with ID =" + std::to_string(id) + " already exists").c_str());
	m_players[id] = _player;
}