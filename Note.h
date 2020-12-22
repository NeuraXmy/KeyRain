//Note.h�� �ַ��༰�ַ���״̬����

#pragma once

#include <qwidget.h>

class QPainter;



//�ַ���״̬
enum class NoteStat
{
	hidden,
	visible,
	cleared,
	lost
};

//�ַ��Ľ�������
enum class BonusMode
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
struct Note final
{

	char ch;

	double x;
	double y;

	NoteStat stat;

	BonusMode bonus;

	//�ַ��Ƿ��ڵ��ʵ���λ
	bool wordBegin;

	//�ַ��������ӵ���ɫ
	mutable QColor particleColor;

	//�ϴβ�����β���ӵ�ʱ��
	int lastCastDragParticleTime;

	Note(char ch, double x, double y, bool wordBegin);

	//�����ַ���is1st���ַ��Ƿ���Ŀǰ�ĵ�һ�� fever��Ŀǰ�Ƿ���feverģʽ
	void Draw(QPainter* painter, bool is1st, bool fever) const;

};