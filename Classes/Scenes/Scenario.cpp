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

	CCTMXTiledMap* p_map = CCTMXTiledMap::create("maps/hexagonal-mini.tmx");
	this->addChild(p_map, 0);
	Size size = p_map->getTileSize();

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
