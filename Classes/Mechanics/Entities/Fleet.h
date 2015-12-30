#pragma once

#include "cocos2d.h"
namespace HexGame 
{
	class Fleet : public cocos2d::Sprite
	{
	public:
		Fleet(float _strength, int _positionX, int _positionY, bool _canMove, int _playerID);
		virtual ~Fleet();
		void setPositionInTiles(int _positionX, int _positionY);
		void setCanMove(bool _canMove);
		bool getCanMove();
		int getPlayerID() { return m_playerID; };
		cocos2d::Vec2 getPositionInHexes() { return cocos2d::Vec2(m_positionHex.first, m_positionHex.second); };
	private:
		int m_playerID;
		float m_strenght;
		std::pair<int, int> m_positionHex;
		bool m_canMove;
	};
}