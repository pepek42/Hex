#include "Player.h"

using namespace HexGame;
using namespace cocos2d;

Player::Player(int _playerID, cocos2d::Color3B _color)
	:m_ID(_playerID), m_color(_color)
{
}


Player::~Player()
{
}

int Player::getID()
{
	return m_ID;
}

cocos2d::Color3B Player::getColor()
{
	return m_color;
}