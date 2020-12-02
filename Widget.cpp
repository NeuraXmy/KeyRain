//Widget.cpp: ¿Ø¼þÀàÐÍ

#include "Widget.h"

#include <qpainter.h>



Widget::Widget() :
	QObject(),
	x(0),
	y(0),
	w(0),
	h(0),
	visible(true),
	inCurrentLayout(false),
	anchor(Anchor::LeftBottom)
{

}



void Widget::Reset()
{

}

void Widget::Update(int time)
{

}

void Widget::Draw(QPainter* painter) const
{

}

void Widget::OnKeyPressEvent(int key)
{

}

void Widget::OnKeyReleaseEvent(int key)
{

}

void Widget::OnMouseMoveEvent(int mouseX, int mouseY)
{

}

void Widget::OnMouseLeftBtnPressEvent()
{

}

void Widget::OnMouseLeftBtnReleaseEvent()
{

}



bool Widget::isMouseHover(int mouseX, int mouseY) const
{
	if(anchor == Anchor::LeftBottom)
		return x <= mouseX && y <= mouseY 
		&& mouseX <= x + w && mouseY <= y + h;
	else
		return x - w / 2 <= mouseX && y - h / 2 <= mouseY 
		&& mouseX <= x + w / 2 && mouseY <= y + h / 2;
}