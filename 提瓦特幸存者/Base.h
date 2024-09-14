#pragma once
#include <graphics.h>
#include <string>
#include <vector>
#include <iostream>

#define PI 3.14159265

const int WIN_WIDTH = 1280;				//窗口大小
const int WIN_HEIGHT = 720;
const int BUTTON_WIDTH = 192;
const int BUTTON_HIGHT = 75;
const int PLAY_ANIMATION = 6;			//角色帧图
const int PLAYER_SPEED = 4;				//玩家速度
const int MONSTER_SPEED = 3;			//怪物速度
const int BULLET_SPEED = 2;				//子弹速度
const int PLAYER_WIDTH = 80;			//贴图大小
const int PLAYER_HEIGHT = 80;
const int MONSTER_WIDTH = 80;
const int MONSTER_HEIGHT = 60;
const int PLAYER_SHADOW_WIDTH = 32;		//阴影大小
const int MONSTER_SHADOW_WIDTH = 48;	

const LPCTSTR PLAYER_LEFT_PATH = _T("img/player_left_%d.png");
const LPCTSTR PLAYER_RIGHT_PATH = _T("img/player_right_%d.png");
const LPCTSTR PLAYER_SHADOW_PATH = _T("img/shadow_player.png");
const LPCTSTR ENEMY_LEFT_PATH = _T("img/enemy_left_%d.png");
const LPCTSTR ENEMY_RIGHT_PATH = _T("img/enemy_right_%d.png");
const LPCTSTR ENEMY_SHADOW_PATH = _T("img/shadow_enemy.png");
const LPCTSTR UI_STAR_IDLE_PATH = _T("img/ui_start_idle.png");
const LPCTSTR UI_STAR_HOVERED_PATH = _T("img/ui_start_hovered.png");
const LPCTSTR UI_STAR_PUSHED_PATH = _T("img/ui_start_pushed.png");
const LPCTSTR UI_QUIT_IDLE_PATH = _T("img/ui_quit_idle.png");
const LPCTSTR UI_QUIT_HOVERED_PATH = _T("img/ui_quit_hovered.png");
const LPCTSTR UI_QUIT_PUSHED_PATH = _T("img/ui_quit_pushed.png");

#pragma comment(lib,"Winmm.lib")
//图片在窗口中的透明背景实现（待学习）
#pragma comment(lib,"MSIMG32.LIB")
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}