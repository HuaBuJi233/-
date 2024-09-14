#pragma once
#include "Base.h"
#include "RESOURCE.h"

class ACTOR
{
private:
	POINT point;							//��ɫ����
	POINT center_point;						//��������
	int speed;								//��ɫ�ٶ�
	int width;								//��ɫ���
	int height;								//��ɫ�߶�
	int shadow_width;						//��ɫ��Ӱ���
private:
	bool is_left = false;					//�ж϶�����
	int timer = 0;							//ʱ�������
	int interval_ms = 0;					//֡��֡��ʱ����
	int index = 0;							//��ǰ����֡����
	IMAGE shadow;							//��ɫ��Ӱ

	RESOURCE* left_frame;
	RESOURCE* right_frame;

	//std::vector<IMAGE*> left_frame_list;	//�󶯻�֡��
	//std::vector<IMAGE*> right_frame_list;	//�Ҷ���֡��
public:
	ACTOR() = default;
	ACTOR(RESOURCE* left_frame_rsc,RESOURCE* right_frame_rsc,const LPCTSTR& path, 
		const int& s,const int& w,const int& h,const int& sw);
	virtual ~ACTOR();
	void play(int delay);					//���Ŷ���
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
