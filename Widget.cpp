#include "Widget.h"

#include <qpainter.h>

Widget::Widget() :
	QObject(),
	x(0),
	y(0),
	w(0),
	h(0),
	visible(true),
	anchor(Anchor::LeftBottom)
{

}

void Widget::Update(int time)
{

}

void Widget::Show(QPainter* painter) const
{
	
}

bool Widget::isMouseHover(int mouseX, int mouseY) const
{
	if(anchor == Anchor::LeftBottom)
		return x <= mouseX && y <= mouseY && mouseX <= x + w && mouseY <= y + h;
	else
		return x - w / 2 <= mouseX && y - h / 2 <= mouseY && mouseX <= x + w / 2 && mouseY <= y + h / 2;
}
