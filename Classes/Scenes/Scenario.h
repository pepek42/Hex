#pragma once

#include "../Mechanics/Fleet.h"

#define COCOS2D_DEBUG 1

class Scenario : public cocos2d::Layer
{
private:
	cocos2d::CCTMXTiledMap*		m_tileMap;
	cocos2d::CCTMXLayer*		m_tileLayer;
	cocos2d::Vector<Fleet*>		m_vFleets;
	Fleet*						m_selectedFleet;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void onMouseDown(cocos2d::Event *e);
    
    // implement the "static create()" method manually
	CREATE_FUNC(Scenario);
};
