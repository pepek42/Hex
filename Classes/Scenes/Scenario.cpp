#include "Scenario.h"

USING_NS_CC;

Scene* Scenario::createScene()
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
bool Scenario::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_tileMap = CCTMXTiledMap::create("maps/tileMap.tmx");
	m_tileLayer = m_tileMap->getLayer("Hexes");
	this->addChild(m_tileMap, 0);

	m_fleet = new CCSprite();
	m_fleet->initWithFile("fleet.png");
	m_fleet->setPosition(ccp(100, 100));

	this->addChild(m_fleet);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Scenario::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    return true;
}

void Scenario::onMouseDown(Event *e)
{
	Node* target = e->getCurrentTarget();
	EventMouse* mouseEvent = (EventMouse*)e;
	Vec2 location = mouseEvent->getLocation();
	Size layerSize = m_tileLayer->getLayerSize();
	for (int x = 0; x < layerSize.width; ++x)
	{
		for (int y = 0; y < layerSize.height; ++y)
		{
			Sprite* tile = m_tileLayer->tileAt(Vec2(x, y));
		}
	}
}

void Scenario::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
