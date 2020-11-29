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

class Note
{
public:

	char ch;

	double x;
	double y;

	int stat;

	bool wordBegin;

	mutable QColor color;

	int lastCastDragParticleTime;

	Note(char ch, double x, double y, bool wordBegin);

	void Show(QPainter* painter, bool is1st, bool fever) const;

private:

};