#include "Fleet.h"

Fleet::Fleet(int _strength, int _positionX, int _positionY, bool _canMove)
	: cocos2d::Sprite(), m_iStrenght(_strength), m_positionHex(_positionX, _positionY), m_canMove(_canMove)
{

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

