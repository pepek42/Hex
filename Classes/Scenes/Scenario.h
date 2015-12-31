#pragma once

#include "../Mechanics/Entities/Fleet.h"

#define COCOS2D_DEBUG 1

namespace HexGame
{
	class ExtendedMap;
	class Scenario : public cocos2d::Layer
	{
	private:
		ExtendedMap*				m_extendedMap;
		cocos2d::CCTMXLayer*		m_tileLayer;
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