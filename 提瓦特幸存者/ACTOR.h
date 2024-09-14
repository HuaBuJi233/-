#pragma once
#include "Base.h"
#include "RESOURCE.h"

class ACTOR
{
private:
	POINT point;							//角色坐标
	POINT center_point;						//中心坐标
	int speed;								//角色速度
	int width;								//角色宽度
	int height;								//角色高度
	int shadow_width;						//角色阴影宽度
private:
	bool is_left = false;					//判断对象朝向
	int timer = 0;							//时间计数器
	int interval_ms = 0;					//帧与帧的时间间隔
	int index = 0;							//当前动画帧索引
	IMAGE shadow;							//角色阴影

	RESOURCE* left_frame;
	RESOURCE* right_frame;

	//std::vector<IMAGE*> left_frame_list;	//左动画帧集
	//std::vector<IMAGE*> right_frame_list;	//右动画帧集
public:
	ACTOR() = default;
	ACTOR(RESOURCE* left_frame_rsc,RESOURCE* right_frame_rsc,const LPCTSTR& path, 
		const int& s,const int& w,const int& h,const int& sw);
	virtual ~ACTOR();
	void play(int delay);					//播放动画
public:
	POINT get_point() const;
	POINT get_center_point() const;
	int get_speed() const;
	int get_width() const;
	int get_height() const;
	int get_shadow_width() const;
	bool get_is_left() const;
	void update(const POINT& p,const bool& il = false);
};
