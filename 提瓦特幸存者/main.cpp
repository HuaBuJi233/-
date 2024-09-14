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
	_stprintf_s(text, _T("��ǰ��ҵ÷֣�%d"), score);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 185));
	outtextxy(10, 10, text);
}

int main()
{
	
	Init_Music(); //���ֳ�ʼ��
	Init_Rect(); //
	STAR_BUTTON star_button(sb_rect, UI_STAR_IDLE_PATH, //��ʼ����ť
		UI_STAR_HOVERED_PATH, UI_STAR_PUSHED_PATH);
	QUIT_BUTTON quit_button(qb_rect, UI_QUIT_IDLE_PATH,
		UI_QUIT_HOVERED_PATH, UI_QUIT_PUSHED_PATH);
	
	HWND gameWnd = initgraph(WIN_WIDTH, WIN_HEIGHT); //�������ڲ����ش��ھ��
	IMAGE menu; //�˵�����
	loadimage(&menu, _T("img/menu.png"));
	IMAGE background; //��Ϸ����
	loadimage(&background, _T("img/background.png"));
	ExMessage msg; //easyX��Ϣ�ṹ��
	int score = 0; //����ͳ��
	std::vector<ENEMY*> enemy_list;	//��������

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
			//���ɵ���
			Generation(enemy_list);
			//�����ƶ�
			peekmessage(&msg);
			bullets1.update(player);
			bullets2.update(player);
			bullets3.update(player);
			player.control(msg);
			for (ENEMY* enemy : enemy_list)
				enemy->move(player);
			//��ײ���
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
			//������Ϸ����
			cleardevice();
			putimage(0, 0, &background);
			//��ɫ����
			for (ENEMY* enemy : enemy_list)
				enemy->play(5);
			player.play(5);
			bullets1.draw();
			bullets2.draw();
			bullets3.draw();
			DrawScore(score);
			FlushBatchDraw();
			//��ѧϰ...
			DWORD end_time = GetTickCount();
			DWORD delta_time = end_time - start_time;
			if (delta_time < 1000 / 75)
				Sleep(1000 / 75 - delta_time);
			if (!IsWindow(gameWnd)) return 0;
		}
		mciSendString(_T("close bgm"), NULL, 0, NULL);
		mciSendString(_T("close hit"), NULL, 0, NULL);
		MessageBox(GetHWnd(), _T("�����������"), _T("��Ϸ����"), MB_OK);
		EndBatchDraw();
	}
	closegraph();
	return 0;
}
