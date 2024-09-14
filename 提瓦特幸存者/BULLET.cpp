#include "BULLET.h"
#include "PLAYER.h"

BULLET::BULLET(const PLAYER& player,int tot,int n)
{
	speed = BULLET_SPEED;
	POINT player_position = player.get_center_point();
	angle = (360.0 / tot) * n;
	double radian = angle * PI / 180.0;
	point.x = player_position.x + 80 * sin(radian);
	point.y = player_position.y + 80 * cos(radian);
}

BULLET::~BULLET()
{
}

void BULLET::update(const PLAYER& player)
{
	//const double TANGENT_SPEED = 2;							//角速度
	POINT player_position = player.get_center_point();
	double radian = angle * PI / 180.0;				//角度转弧度
	point.x = player_position.x + 100 * sin(radian);
	point.y = player_position.y + 100 * cos(radian);
	if (angle == 360.0) angle = 0;							//判断是否转一圈
	else angle += speed;
}

void BULLET::re_build(const PLAYER& player, int tot, int n)
{
	POINT player_position = player.get_center_point();
	angle = (360.0 / tot) * n;
	double radian = angle * PI / 180.0;
	point.x = player_position.x + 100 * sin(radian);
	point.y = player_position.y + 100 * cos(radian);
}

void BULLET::draw() const
{
	setlinecolor(RGB(255, 150, 0));
	setfillcolor(RGB(200, 75, 10));
	fillcircle(point.x, point.y, 10);
}

POINT BULLET::get_point() const
{
	return point;
}
