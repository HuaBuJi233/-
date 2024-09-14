#pragma once
#include "Base.h"
#include"ACTOR.h"

class PLAYER;
class BULLET;

class ENEMY :public ACTOR
{
private:
	enum class BUNDARY {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
public:
	ENEMY() = default;
	ENEMY(RESOURCE* left_frame_rsc, RESOURCE* right_frame_rsc, const LPCTSTR& l3,
		const int& s, const int& w, const int& h, const int& sw);
	~ENEMY();
public:
	void move(const PLAYER& player);
	bool checkcollision(const BULLET& bullet);
};

