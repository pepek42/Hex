#include "Fleet.h"

using namespace cocos2d;
using namespace HexGame;

Fleet::Fleet(float _strength, int _positionX, int _positionY, bool _canMove, int _playerID)
	: cocos2d::Sprite(), m_strenght(_strength), m_positionHex(_positionX, _positionY), m_canMove(_canMove), m_playerID(_playerID)
{
	initWithFile("fleet.png");
	setAnchorPoint(ccp(0, 0));
}


Fleet::~Fleet()
{

}

void Fleet::setPositionInTiles(int _positionX, int _positionY)
{
	m_positionHex = std::make_pair(_positionX, _positionY);
}

void Fleet::setCanMove(bool _canMove)
{
	m_canMove = _canMove;
}

bool Fleet::getCanMove()
{
	return m_canMove;
}

