#pragma once

#include "../Mechanics/Entities/Fleet.h"

#define COCOS2D_DEBUG 1

namespace HexGame
{
	class ExtendedMap;
	class Scenario : public cocos2d::Layer
	{
	private:
		cocos2d::CCTMXTiledMap*		m_tileMap;
		ExtendedMap*				m_extendedMap;
		cocos2d::CCTMXLayer*		m_tileLayer;
		cocos2d::Vector<Fleet*>		m_vFleets;			// michal ppk
		Fleet*						m_selectedFleet;	// michal ppk
	public:
		static cocos2d::Scene* createScene();

		virtual bool init();

		// a selector callback
		void menuCloseCallback(cocos2d::Ref* pSender);

		void onMouseDown(cocos2d::Event *e);

		// implement the "static create()" method manually
		CREATE_FUNC(Scenario);
	};
}