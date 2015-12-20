#pragma once

#include "cocos2d.h"

#define COCOS2D_DEBUG 1

class Scenario : public cocos2d::Layer
{
private:
	cocos2d::CCTMXTiledMap* m_tileMap;
	cocos2d::CCSprite* m_fleet;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(Scenario);
};
