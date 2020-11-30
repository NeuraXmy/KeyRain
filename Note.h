#pragma once

#include <qwidget.h>

class QPainter;

enum NoteStat
{
	hidden,
	visible,
	cleared,
	lost
};

enum BonusMode
{
	noBonus,
	fast,
	slow,
	reverse,
	random,
	bonusNum
};

class Note
{
public:

	char ch;

	double x;
	double y;

	int stat;

	int bonus;

	bool wordBegin;

	mutable QColor color;

	int lastCastDragParticleTime;

	Note(char ch, double x, double y, bool wordBegin);

	void Show(QPainter* painter, bool is1st, bool fever) const;

private:

};