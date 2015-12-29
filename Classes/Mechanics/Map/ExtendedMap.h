#pragma once

#include "cocos2d.h"

using namespace cocos2d;

namespace HexGame
{
	class ExtendedMapInfo;
	class Fleet;

	class ExtendedMap : public cocos2d::Node
	{
	protected:
		cocos2d::Vector<Fleet*>		m_vFleets;
	public:
		ExtendedMap();
		virtual ~ExtendedMap();

		static ExtendedMap* create(const std::string& mapFile);
		bool initWithTMXFile(const std::string& mapFile);
		void buildWithMapInfo(ExtendedMapInfo* mapInfo);

		void addFleet(Fleet* fleet);
	};
}

