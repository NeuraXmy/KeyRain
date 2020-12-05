//SlideBar.cpp: 按钮控件类型

#include "SlideBar.h"
#include "Define.h"

#include <qpainter.h>



SlideBar::SlideBar(double* value, double minVal, double maxVal)
	: Widget()
	, value(value)
	, minVal(minVal)
	, maxVal(maxVal)

{

}



void SlideBar::Reset()
{
	isDown = isHover = false;
}

void SlideBar::Draw(QPainter* painter) const
{
	if (!visible)
	{
		return;
	}

	if (anchor == Anchor::LeftBottom)
		painter->translate(x, y);
	else if (anchor == Anchor::Center)
		painter->translate(x - w / 2, y - h / 2);

	if (isDown)
		painter->setBrush(Def::btnDownColor);
	else if (isHover)
		painter->setBrush(Def::btnHoverColor);
	else
		painter->setBrush(Def::btnColor);


	painter->drawRect(0, h / 2 - 1, w, 2);

	painter->translate(w * (*value - minVal) / (maxVal - minVal), 0);
	painter->drawRect(-5, 1, 10, h - 2);
	painter->translate(-w * (*value - minVal) / (maxVal - minVal), 0);


	if (anchor == Anchor::LeftBottom)
		painter->translate(-x, -y);
	else if (anchor == Anchor::Center)
		painter->translate(w / 2 - x, h / 2 - y);
}



void SlideBar::OnMouseMoveEvent(int mouseX, int mouseY)
{
	isHover = isMouseHover(mouseX, mouseY);

	if (isDown)
	{
		if (anchor == Anchor::LeftBottom)
			*value = (maxVal - minVal) * std::min(1.0, std::max(0.0, double(mouseX - x) / w)) + minVal;
		else if (anchor == Anchor::Center)
			*value = (maxVal - minVal) * std::min(1.0, std::max(0.0, double(mouseX - x + w / 2) / w)) + minVal;
	}
}

void SlideBar::OnMouseLeftBtnPressEvent()
{
	if (!isHover)
	{
		return;
	}

	if (!isDown)
	{
		isDown = true;
	}
}

void SlideBar::OnMouseLeftBtnReleaseEvent()
{
	if (isDown)
	{
		isDown = false;
	}
}

