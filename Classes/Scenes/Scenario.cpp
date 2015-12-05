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

	m_tileMap = CCTMXTiledMap::create("maps/hexagonal-mini.tmx");
	this->addChild(m_tileMap, 0);
	Size size = m_tileMap->getTileSize();

	CCTMXObjectGroup* objectGroup = m_tileMap->objectGroupNamed("Objects");

	if (objectGroup == NULL){
		throw "WTF";
	}

	ValueMap spawnPoint = objectGroup->getObject("Test");

	//for (auto it = spawnPoint.begin(); it != spawnPoint.end(); ++it)
	//{
	//	CCLOG("%s", it->first);
	//	CCLOG("%s", it->second.asString());
	//}

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	float height = spawnPoint["height"].asFloat();

	m_fleet = new CCSprite();
	m_fleet->initWithFile("fleet.png");
	m_fleet->setPosition(ccp(x, y + height));

	this->addChild(m_fleet);


	//Create a "one by one" touch event listener (processes one touch at a time)
	auto listener = EventListenerMouse::create();

	//Trigger when moving touch
	listener->onMouseDown = [](Event* event){
		auto target = static_cast<CCSprite*>(event->getCurrentTarget());

		auto e = static_cast<EventMouse*>(event);
		
		target->setPosition(Vec2(e->getCursorX(), e->getCursorY()));
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, m_fleet);

	//Vector<Node*> pChildrenArray = Pmap->getChildren();

	//for (auto it = pChildrenArray.begin(); it != pChildrenArray.end(); ++it)
	//{

	//}
    
    return true;
}

void Scenario::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
