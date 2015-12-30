#include "Scenario.h"
#include "../Mechanics/Map/ExtendedMap.h"

USING_NS_CC;

Scene* HexGame::Scenario::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = Scenario::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HexGame::Scenario::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_extendedMap = ExtendedMap::create("maps/tileMap.tmx", "maps/extendedMap.xml", this);
	m_tileLayer = m_extendedMap->getLayer("Hexes");
	this->addChild(m_extendedMap, 0);
	CCASSERT(m_extendedMap->getParent() == this, "Scenario is not extended map's parent!");

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Scenario::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    return true;
}

void HexGame::Scenario::onMouseDown(Event *e)
{
	Node* target = e->getCurrentTarget();
	EventMouse* mouseEvent = (EventMouse*)e;
	
	m_extendedMap->actionAt(ccp(mouseEvent->getCursorX(), mouseEvent->getCursorY()));
}

void HexGame::Scenario::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
