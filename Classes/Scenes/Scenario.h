#pragma once

#include "ContentManagers\ScenarioManager.h"

class HexMap;

class Scenario : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(Scenario);

private:
	HexMap* m_map;
	ScenarioManager m_scenarioManager;
};
