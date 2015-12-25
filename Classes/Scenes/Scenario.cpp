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

	m_selectedFleet = nullptr;

	m_tileMap = CCTMXTiledMap::create("maps/tileMap.tmx");
	m_tileLayer = m_tileMap->getLayer("Hexes");
	this->addChild(m_tileMap, 0);

	Fleet* testFleet = new Fleet(random() % 5 + 1, 1, 48, true);
	testFleet->initWithFile("fleet.png");
	testFleet->setPosition(ccp(100, 100));
	this->addChild(testFleet);

	m_vFleets.pushBack(testFleet);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Scenario::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    return true;
}

void Scenario::onMouseDown(Event *e)
{
	Node* target = e->getCurrentTarget();
	EventMouse* mouseEvent = (EventMouse*)e;
	Size layerSize = m_tileLayer->getLayerSize();
	Size tileSize = m_tileMap->getTileSize();
	float mouseX = mouseEvent->getCursorX();
	float mouseY = mouseEvent->getCursorY();

	for (auto it = m_vFleets.begin(); it != m_vFleets.end(); ++it)
	{
		Vec2 basePosition = (*it)->getPosition();
		Size spriteSize = (*it)->getContentSize();
		basePosition.x -= (spriteSize.width / 2);
		basePosition.y -= (spriteSize.height / 2);
		if (basePosition.x < mouseX && basePosition.y < mouseY)
		{
			if (mouseEvent->getCursorX() < (basePosition.x + spriteSize.width) && mouseEvent->getCursorY() < (basePosition.y + spriteSize.height))
			{
				if (m_selectedFleet == *it) {
					m_selectedFleet = nullptr;
				}
				else {
					m_selectedFleet = *it;
				}
				return;
			}
		}
	}
	if (m_selectedFleet == nullptr || !m_selectedFleet->getCanMove())
		return;
	for (int x = 0; x < layerSize.width; ++x)
	{
		for (int y = 0; y < layerSize.height; ++y)
		{
			Sprite* tile = m_tileLayer->tileAt(Vec2(x, y));
			Vec2 spriteCenter = Vec2(tile->getPositionX() + tileSize.width / 2, tile->getPositionY() + tileSize.height / 2);
			// michal ppk to do tile detection
			Vec2 diff = spriteCenter - ccp(mouseX, mouseY);
			if (diff.length() < tileSize.height / 2)
			{
				m_selectedFleet->setPositionInTiles(x, y);
				m_selectedFleet->setPosition(spriteCenter.x, spriteCenter.y);
				m_selectedFleet->setCanMove(false);
				m_selectedFleet = nullptr;
				return;
			}
		}
	}
}

void Scenario::menuCloseCallback(Ref* pSender)
{
	for (auto it = m_vFleets.begin(); it != m_vFleets.end(); ++it)
	{
		delete *it;
	}
	m_vFleets.clear();

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
