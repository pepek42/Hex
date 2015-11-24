#pragma once

class Hex;

class HexMap
{
public:
	HexMap();
	virtual ~HexMap();
private:
	Hex** m_pHexMap;
};

