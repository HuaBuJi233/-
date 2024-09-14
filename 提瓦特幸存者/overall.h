#pragma once
#include "PLAYER.h"
#include "ENEMY.h"
#include "BULLET.h"
#include "BUTTON.h"

RESOURCE player_left_frame(PLAYER_LEFT_PATH, PLAY_ANIMATION);
RESOURCE player_right_frame(PLAYER_RIGHT_PATH, PLAY_ANIMATION);
RESOURCE enemy_left_frame(ENEMY_LEFT_PATH, PLAY_ANIMATION);
RESOURCE enemy_right_frame(ENEMY_RIGHT_PATH, PLAY_ANIMATION);

PLAYER player(& player_left_frame, & player_right_frame, PLAYER_SHADOW_PATH,
	PLAYER_SPEED, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_SHADOW_WIDTH);

BULLET bullets1(player, 3, 1);
BULLET bullets2(player, 3, 2);
BULLET bullets3(player, 3, 3);

RECT sb_rect, qb_rect;

void Init_Rect()
{
	sb_rect.left = (WIN_WIDTH - BUTTON_WIDTH) / 2;
	sb_rect.right = sb_rect.left + BUTTON_WIDTH;
	sb_rect.top = 430;
	sb_rect.bottom = sb_rect.top + BUTTON_HIGHT;
	qb_rect.left = (WIN_WIDTH - BUTTON_WIDTH) / 2;
	qb_rect.right = qb_rect.left + BUTTON_WIDTH;
	qb_rect.top = 550;
	qb_rect.bottom = qb_rect.top + BUTTON_HIGHT;
}


void Init_Music()
{
	//“Ù¿÷ππΩ®
	mciSendString(_T("open mp3/BGM.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open mp3/HIT.mp3 alias hit"), NULL, 0, NULL);
	mciSendString(_T("setaudio hit volume to 200"), NULL, 0, NULL);
}
