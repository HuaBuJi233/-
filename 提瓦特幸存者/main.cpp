#include "overall.h"
#include <windows.h>

void Generation(std::vector<ENEMY*>& enemy_list)
{
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemy_list.push_back(new ENEMY(&enemy_left_frame, &enemy_right_frame, ENEMY_SHADOW_PATH,
			MONSTER_SPEED, MONSTER_WIDTH, MONSTER_HEIGHT, MONSTER_SHADOW_WIDTH));
}

void DrawScore(int score)
{
	static TCHAR text[64];
	_stprintf_s(text, _T("当前玩家得分：%d"), score);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 185));
	outtextxy(10, 10, text);
}

int main()
{
	
	Init_Music(); //音乐初始化
	Init_Rect(); //
	STAR_BUTTON star_button(sb_rect, UI_STAR_IDLE_PATH, //初始化按钮
		UI_STAR_HOVERED_PATH, UI_STAR_PUSHED_PATH);
	QUIT_BUTTON quit_button(qb_rect, UI_QUIT_IDLE_PATH,
		UI_QUIT_HOVERED_PATH, UI_QUIT_PUSHED_PATH);
	
	HWND gameWnd = initgraph(WIN_WIDTH, WIN_HEIGHT); //创建窗口并返回窗口句柄
	IMAGE menu; //菜单背景
	loadimage(&menu, _T("img/menu.png"));
	IMAGE background; //游戏背景
	loadimage(&background, _T("img/background.png"));
	ExMessage msg; //easyX消息结构体
	int score = 0; //分数统计
	std::vector<ENEMY*> enemy_list;	//敌人容器

	while (1)
	{
		BeginBatchDraw();
		peekmessage(&msg);
		putimage(0, 0, &menu);
		star_button.draw();
		quit_button.draw();
		star_button.event(msg);
		quit_button.event(msg);
		star_button.draw();
		quit_button.draw();
		FlushBatchDraw();
		if (GAME_STAR || GAME_QUIT) break;
		if (!IsWindow(gameWnd)) return 0;
	}
	EndBatchDraw();
	if (GAME_STAR)
	{
		BeginBatchDraw();
		while (player.get_player_condition())
		{
			DWORD start_time = GetTickCount();
			//生成敌人
			Generation(enemy_list);
			//对象移动
			peekmessage(&msg);
			bullets1.update(player);
			bullets2.update(player);
			bullets3.update(player);
			player.control(msg);
			for (ENEMY* enemy : enemy_list)
				enemy->move(player);
			//碰撞检测
			for (int i = 0; i < enemy_list.size(); i++)
			{
				player.checkcollision(*enemy_list[i]);
				if (!enemy_list[i]->checkcollision(bullets1) ||
					!enemy_list[i]->checkcollision(bullets2) ||
					!enemy_list[i]->checkcollision(bullets3))
				{
					mciSendString(_T("play hit from 0"), NULL, 0, NULL);
					ENEMY* enemy = enemy_list[i];
					std::swap(enemy_list[i], enemy_list.back());
					enemy_list.pop_back();
					delete enemy;
					score++;
				}
			}
			//绘制游戏画面
			cleardevice();
			putimage(0, 0, &background);
			//角色绘制
			for (ENEMY* enemy : enemy_list)
				enemy->play(5);
			player.play(5);
			bullets1.draw();
			bullets2.draw();
			bullets3.draw();
			DrawScore(score);
			FlushBatchDraw();
			//待学习...
			DWORD end_time = GetTickCount();
			DWORD delta_time = end_time - start_time;
			if (delta_time < 1000 / 75)
				Sleep(1000 / 75 - delta_time);
			if (!IsWindow(gameWnd)) return 0;
		}
		mciSendString(_T("close bgm"), NULL, 0, NULL);
		mciSendString(_T("close hit"), NULL, 0, NULL);
		MessageBox(GetHWnd(), _T("玩家已阵亡！"), _T("游戏结束"), MB_OK);
		EndBatchDraw();
	}
	closegraph();
	return 0;
}
