#include "PLAYER.h"
#include "ENEMY.h"

PLAYER::PLAYER(RESOURCE* left_frame_rsc, RESOURCE* right_frame_rsc, const LPCTSTR& l3,
	const int& s, const int& w, const int& h, const int& sw)
	:ACTOR(left_frame_rsc,right_frame_rsc,l3,s,w,h,sw)
{
	HP = 3;
	POINT player_staget_point = { 600,320 };
	update(player_staget_point);
}

PLAYER::~PLAYER()
{
}

void PLAYER::control(ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		//std::cout << "键盘按下\n";
		switch (msg.vkcode)
		{
		case VK_UP: UP = true;
			break;
		case VK_LEFT: LEFT = true;
			break;
		case VK_DOWN: DOWN = true;
			break;
		case VK_RIGHT: RIGHT = true;
			break;
		}
	}
	else if (msg.message == WM_KEYUP)
	{
		//std::cout << "键盘回弹\n";
		switch (msg.vkcode)
		{
		case VK_UP: UP = false;
			break;
		case VK_LEFT: LEFT = false;
			break;
		case VK_DOWN: DOWN = false;
			break;
		case VK_RIGHT: RIGHT = false;
			break;
		}
	}
	move();
}

void PLAYER::move()
{
	POINT point = get_point();
	bool is_left = get_is_left();
	int x_val = 0;
	int y_val = 0;

	if (UP) y_val = -PLAYER_SPEED;
	if (DOWN) y_val = PLAYER_SPEED;
	if (RIGHT) x_val = PLAYER_SPEED;
	if (LEFT)  x_val = -PLAYER_SPEED;
	double speed = PLAYER_SPEED;
	double distance = sqrt(x_val * x_val + y_val * y_val);
	if (distance != 0)
	{
		double speed_xval = x_val / distance;
		double speed_yval = y_val / distance;
		if ((point.x + (PLAYER_SPEED * speed_xval) <= 1200) && (point.x + (PLAYER_SPEED * speed_xval) >= 0))
		{
			point.x += (PLAYER_SPEED * speed_xval);
			//std::cout << " 人物x更新:" <<PLAYER_SPEED * speed_xval<< "---" << point.x << std::endl;
		}
		if (point.y + (PLAYER_SPEED * speed_yval) <= 640 && (point.y + (PLAYER_SPEED * speed_yval) >= 0))
		{
			point.y += (PLAYER_SPEED * speed_yval);
			//std::cout << "人物y更新:" << PLAYER_SPEED * speed_yval << "---" << point.y << std::endl;
		}
	}
	if (x_val < 0)
		is_left = true;
	else if (x_val > 0)
		is_left = false;
	update(point, is_left);
}

bool PLAYER::checkcollision(const ENEMY& enemy)
{
	POINT p1 = get_center_point();
	POINT p2 = enemy.get_point();
	int enemy_width = enemy.get_width();
	int enemy_height = enemy.get_height();

	//测试
	/*std::cout << "人物中心点（" << p1.x << "," << p1.y<<"）\t" <<
		"怪物坐标点（" << p2.x << "," << p2.y << "）\n";*/
		
	if ((p2.x <= p1.x && p1.x <= p2.x + enemy_width) &&
		(p2.y <= p1.y && p1.y <= p2.y + enemy_height))
	{
		HP = 0;
		return false;
	}
}

bool PLAYER::get_player_condition() const
{
	if (HP == 0)
		return false;
	else return true;
}
