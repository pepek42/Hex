#pragma once

#include "cocos2d.h"

class Scenario;

/**
*  ScenarioManager class. Responsible for loading and saving scenario. 
*/
class ScenarioManager
{
public:
	ScenarioManager();
	virtual ~ScenarioManager();

	bool load(Scenario* _scenario, cocos2d::CCString _path);
	bool save(Scenario* _scenario, cocos2d::CCString _path);
};

