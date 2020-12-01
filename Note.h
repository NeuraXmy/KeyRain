//Note.h�� �ַ��༰�ַ���״̬����

#pragma once

#include <qwidget.h>

class QPainter;



//�ַ���״̬
enum NoteStat
{
	hidden,
	visible,
	cleared,
	lost
};

//�ַ��Ľ�������
enum BonusMode
{
	noBonus,
	fast,
	slow,
	reverse,
	random,
	bonusNum
};



/**
* Note
* ��Ϸ�е�һ���ַ�����
*/
struct Note
{
	char ch;

	double x;
	double y;

	int stat;

	int bonus;

	//�ַ��Ƿ��ڵ��ʵ���λ
	bool wordBegin;

	//�ַ��������ӵ���ɫ
	mutable QColor particleColor;

	//�ϴβ�����β���ӵ�ʱ��
	int lastCastDragParticleTime;

	Note(char ch, double x, double y, bool wordBegin);

	//�����ַ���is1st���ַ��Ƿ���Ŀǰ�ĵ�һ�� fever��Ŀǰ�Ƿ���feverģʽ
	void Show(QPainter* painter, bool is1st, bool fever) const;
};