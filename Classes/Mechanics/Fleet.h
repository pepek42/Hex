#pragma once

#include "cocos2d.h"

class Fleet: public cocos2d::Sprite
{
public:
	Fleet(int _strength, int _positionX, int _positionY, bool _canMove);
	virtual ~Fleet();
	void setPositionInTiles(int _positionX, int _positionY);
	void setCanMove(bool _canMove);
	bool getCanMove();
private:
	int m_iStrenght;
	std::pair<int, int> m_positionHex;
	bool m_canMove;
};

