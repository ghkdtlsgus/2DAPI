#pragma once
class MapControl
{
protected:
	float Map_X;
	float Map_Y;
	float Charater_X;
	float Charater_Y;
protected:
	virtual void printz() = 0;
public:
	float GetMap_X() { return Map_X; }
	float GetMap_Y()  { return Map_Y; }
public:
	MapControl();
	~MapControl();
};

