#pragma once

#include "cocos2d.h"

enum class HexType : unsigned char { 
	EmptyHex, 
	Star,
	Nebula,
	BlackHole
};

class Hex
{
public:
	Hex();
	virtual ~Hex();
private:
	HexType m_ehexType;
	cocos2d::Sprite* m_sHexSprite;
};