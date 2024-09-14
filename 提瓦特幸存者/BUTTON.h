#pragma once
#include "Base.h"

bool GAME_STAR = false;						//游戏运行标识
bool GAME_QUIT = false;

class BUTTON
{
public:
	BUTTON(const RECT& r,const LPCTSTR& l1,
		const LPCTSTR& l2,const LPCTSTR& l3)
	{
		rect = r;
		state = Status::Idle;
		loadimage(&hovered, l1);
		loadimage(&idle, l2);
		loadimage(&pushed, l3);
	}
	~BUTTON() = default;
public:
	void draw()
	{
		switch (state)
		{
		case Status::Idle:
			putimage(rect.left, rect.top, &idle);
			break;
		case Status::Hovered:
			putimage(rect.left, rect.top, &hovered);
			break;
		case Status::Pushed:
			putimage(rect.left, rect.top, &pushed);
			break;
		}
	}

	bool check_mouse(int x,int y)
	{
		return (rect.left <= x && x <= rect.right) && (rect.top <= y && y <= rect.bottom);
	}

	void event(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			if (check_mouse(msg.x, msg.y)) state = Status::Hovered;
			else state = Status::Idle;
			break;
		case WM_LBUTTONDOWN:
			if (check_mouse(msg.x, msg.y) && state==Status::Hovered)
				state = Status::Pushed;
			break;
		case WM_LBUTTONUP:
			if (check_mouse(msg.x, msg.y) && state == Status::Pushed)
			{
				state = Status::Hovered;
				onclick();
			}
			break;
		}
	}
protected:
	virtual void onclick() = 0;
public:
	enum class Status
	{
		Idle = 0,
		Hovered,
		Pushed
	};
private:
	RECT rect;
	IMAGE idle;
	IMAGE hovered;
	IMAGE pushed;
	Status state;
};

class STAR_BUTTON:public BUTTON
{
public:
	STAR_BUTTON(const RECT& r, const LPCTSTR& l1,
		const LPCTSTR& l2, const LPCTSTR& l3)
		:BUTTON(r, l1, l2, l3){}
	~STAR_BUTTON() = default;
protected:
	void onclick()
	{
		GAME_STAR = true;
		mciSendString(_T("setaudio bgm volume to 50"), NULL, 0, NULL);
		mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
	}
};

class QUIT_BUTTON:public BUTTON
{
public:
	QUIT_BUTTON(const RECT& r, const LPCTSTR& l1,
		const LPCTSTR& l2, const LPCTSTR& l3)
		:BUTTON(r, l1, l2, l3){}
	~QUIT_BUTTON() = default;
protected:
	void onclick()
	{
		GAME_QUIT = true;
	}
};