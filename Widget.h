#pragma once

#include <qobject.h>

enum Anchor
{
	Center,
	LeftBottom
};

class QPainter;

class Widget : public QObject
{
	Q_OBJECT

public:

	int x;
	int y;
	int w;
	int h;

	int anchor;

	bool visible;

	Widget();

	virtual void Update(int time);

	virtual void Show(QPainter* painter) const;

	bool isMouseHover(int mouseX, int mouseY) const;

};
