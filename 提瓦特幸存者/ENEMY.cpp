#include "ENEMY.h"
#include "PLAYER.h"
#include "BULLET.h"
#include <cmath>

ENEMY::ENEMY(RESOURCE* left_frame_rsc, RESOURCE* right_frame_rsc, const LPCTSTR& l3,
	const int& s, const int& w, const int& h, const int& sw)
	:ACTOR(left_frame_rsc, right_frame_rsc,l3,s,w,h,sw)
{
	BUNDARY start = BUNDARY(rand() % 4);
	int end_x, end_y = 0;
	POINT p1;
	switch (start)
	{
	case BUNDARY::UP:
		end_y = -50;
		end_x = rand() % WIN_WIDTH;
		break;
	case BUNDARY::DOWN:
		end_y = WIN_HEIGHT + 50;
		end_x = rand() % WIN_WIDTH;
		break;
	case BUNDARY::LEFT:
		end_x = -50;
		end_y = rand() % WIN_HEIGHT;
		break;
	case BUNDARY::RIGHT:
		end_x = WIN_WIDTH + 50;
		end_y = rand() % WIN_HEIGHT;
		break;
	}
	p1.x = end_x;
	p1.y = end_y;
	update(p1);
}

ENEMY::~ENEMY()
{
}


void ENEMY::move(const PLAYER& player)
{
	
	POINT p1 = get_point();
	POINT p2 = player.get_point();
	bool is_left = get_is_left();
	/*
	* //Ê§°ÜµÄ¸ú×ÙÊµÏÖ
	if (p1.x != p2.x||p1.y!=p2.y)
	{
		double angle = atan2(p2.y - p1.y, p2.x - p1.x);
		double ang_degrees = angle * 180.0 / PI;
		p1.x += MONSTER_SPEED * cos(ang_degrees);
		p1.y += MONSTER_SPEED * sin(ang_degrees);
		if (ang_degrees<90 && ang_degrees>-90) is_left = false;
		if (ang_degrees > 90 || ang_degrees < -90) is_left = true;
		update(p1, is_left);
	}
	*/
	int x_val = p2.x - p1.x;
	int y_val = p2.y - p1.y;
	double distance = sqrt(x_val * x_val + y_val * y_val);
	if (distance != 0)
	{
		double speed_xval = x_val / distance;
		double speed_yval = y_val / distance;
		p1.x += (MONSTER_SPEED * speed_xval);
		p1.y += (MONSTER_SPEED * speed_yval);
	}
	if (x_val < 0)
		is_left = true;
	else is_left = false;
	update(p1, is_left);
}

bool ENEMY::checkcollision(const BULLET& bullet)
{
	POINT p1 = get_point();
	POINT p2 = bullet.get_point();
	if ((p2.x >= p1.x && p2.x <= p1.x + get_width()) &&
		(p2.y >= p1.y && p2.y <= p1.y + get_height()))
		return false;
	else return true;
}

