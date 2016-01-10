#pragma once

#include "cocos2d.h"
#include <map>

using namespace cocos2d;

namespace HexGame
{
	class ExtendedMapInfo;
	class Fleet;
	class Scenario;
	class Player;
	class Hex;

	enum class Relation
	{
		Ally,
		Neutral,
		Hostile
	};

	class ExtendedMap : public cocos2d::CCTMXTiledMap
	{
	protected:
		Fleet*						m_selectedFleet;
		CCTMXLayer*					m_tileLayer;
		Scenario*					m_parentScene;
		int							m_playerCount;
		int							m_currentPlayerTurnID;
		std::map<int, Player*>		m_players;
		cocos2d::Vector<Fleet*>		m_vFleets;
		std::vector<std::string>	m_strengthValueNames;
	public:
		ExtendedMap();
		virtual ~ExtendedMap();

		static ExtendedMap* create(const std::string& tmxFile, const std::string& mapFile, Scenario * _parentScenario);
		bool initWithMapFile(const std::string& mapFile);
		void buildWithMapInfo(ExtendedMapInfo* mapInfo);

		void addFleet(Fleet* fleet);
		void actionAt(Vec2 mouseClickPosition);

		void setPlayerCount(int _playerCount);
		void setCurrentPlayerTurnID(int _currentPlayerTurnID);
		int getPlayerCount();
		int getCurrentPlayerTurnID();

		void addPlayer(Player* _player);

		void updateMap();

		Vec2 positionToHexPosition(Vec2 pointPosition);

		Relation getRelationWithPlayer(int playerID);

		//void endTurn();
	};
}

