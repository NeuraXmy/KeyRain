//Note.h： 字符类及字符的状态属性

#pragma once

#include <qwidget.h>

class QPainter;



//字符的状态
enum class NoteStat
{
	hidden,
	visible,
	cleared,
	lost
};

//字符的奖励类型
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
* 游戏中的一个字符类型
*/
struct Note final
{

	char ch;

	double x;
	double y;

	NoteStat stat;

	BonusMode bonus;

	//字符是否在单词的首位
	bool wordBegin;

	//字符产生粒子的颜色
	mutable QColor particleColor;

	//上次产生拖尾粒子的时间
	int lastCastDragParticleTime;

	Note(char ch, double x, double y, bool wordBegin);

	//绘制字符，is1st：字符是否是目前的第一个 fever：目前是否在fever模式
	void Draw(QPainter* painter, bool is1st, bool fever) const;

};