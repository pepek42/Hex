#pragma once

#include "cocos2d.h"

namespace HexGame
{
	class Player
	{
	private:
		int					m_ID;
		cocos2d::Color3B	m_color;
	public:
		Player(int _playerID, cocos2d::Color3B _color);
		virtual ~Player();

		int getID();
		cocos2d::Color3B getColor();
	};
}