#pragma once
#include "Base.h"

class PLAYER;

class BULLET
{
private:
	POINT point;
	double angle;
	int speed;
public:
	BULLET() = default;
	BULLET(const PLAYER& player,int tot,int n);
	~BULLET();
	void update(const PLAYER& player);
	void re_build(const PLAYER& player, int tot, int n);
	void draw() const;
public:
	POINT get_point() const;
};

