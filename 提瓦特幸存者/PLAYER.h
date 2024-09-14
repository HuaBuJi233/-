#pragma once
#include "Base.h"
#include"ACTOR.h"

class ENEMY;

class PLAYER :public ACTOR
{
private:
	bool UP = false;
	bool DOWN = false;
	bool LEFT = false;
	bool RIGHT = false;
private:
	int HP;
public:
	PLAYER() = default;
	PLAYER(RESOURCE* left_frame_rsc, RESOURCE* right_frame_rsc, const LPCTSTR& l3,
		const int &s, const int& w, const int& h, const int& sw);
	~PLAYER();
	void control(ExMessage& msg);
	void move();
	bool checkcollision(const ENEMY& enemy);
public:
	bool get_player_condition() const;
};

