#include "ACTOR.h"

ACTOR::ACTOR(RESOURCE* left_frame_rsc,RESOURCE* right_frame_rsc,
	const LPCTSTR& l3,const int& s,const int& w, const int& h, const int& sw)
{
	speed = s;
	width = w;
	height = h;
	shadow_width = sw;
	center_point.x = point.x + width / 2;
	center_point.y = point.y + height / 2;
	interval_ms = 50;
	loadimage(&shadow, l3);
	left_frame = left_frame_rsc;
	right_frame = right_frame_rsc;
}

ACTOR::~ACTOR()
{

}

POINT ACTOR::get_point() const
{
	return point;
}

POINT ACTOR::get_center_point() const
{
	return center_point;
}

int ACTOR::get_speed() const
{
	return speed;
}

int ACTOR::get_width() const
{
	return width;
}

int ACTOR::get_height() const
{
	return height;
}

int ACTOR::get_shadow_width() const
{
	return shadow_width;
}

bool ACTOR::get_is_left() const
{
	return is_left;
}

void ACTOR::update(const POINT& p,const bool& il)
{
	point = p;
	center_point.x = point.x + width / 2;
	center_point.y = point.y + height / 2;
	is_left = il;
}

void ACTOR::play(int delay)
{
	timer += delay;
	if (timer >= interval_ms)
	{
		index++;
		index %= PLAY_ANIMATION;
		timer = 0;
	}
	putimage_alpha((point.x + width / 2 - shadow_width / 2), (point.y + height - 8), &shadow);
	if(is_left)
		putimage_alpha(point.x, point.y, left_frame->frame_list[index]);
	else putimage_alpha(point.x, point.y, right_frame->frame_list[index]);
}
