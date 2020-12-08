//Switcher.cpp: 开关控件类型

#include "Switcher.h"
#include "Define.h"
#include "SoundManager.h"

#include <qpainter.h>



Switcher::Switcher(bool* value)
	: Widget()
	, value(value)
	, isDown(false)
	, isHover(false)
{

}



void Switcher::Reset()
{
	isDown = isHover = false;
}

void Switcher::Draw(QPainter* painter) const
{
	if (!visible)
	{
		return;
	}

	std::string str = *value ? "ON" : "OFF";

	if (anchor == Anchor::LeftBottom)
		painter->translate(x, y);
	else if (anchor == Anchor::Center)
		painter->translate(x - w / 2, y - h / 2);

	painter->setBrush(Qt::transparent);

	if (isDown)
		painter->setPen(Def::btnDownColor);
	else if (isHover)
		painter->setPen(Def::btnHoverColor);
	else
		painter->setPen(Def::btnColor);

	auto pen = painter->pen();
	auto lastPen = pen;
	pen.setWidth(2);
	painter->setPen(pen);

	painter->drawRect(0, 0, w, h);

	{
		auto font = painter->font();
		font.setPixelSize(h - 4);
		painter->setFont(font);

		QFontMetrics m(painter->font());
		int fontW = m.width(str.c_str());
		int fontH = m.height();

		painter->scale(1.0, -1.0);
		painter->drawText(w / 2 - fontW / 2 + 4, -h / 2 + fontH / 2 - 4, str.c_str());
		painter->scale(1.0, -1.0);
	}

	if (anchor == Anchor::LeftBottom)
		painter->translate(-x, -y);
	else if (anchor == Anchor::Center)
		painter->translate(w / 2 - x, h / 2 - y);

	painter->setPen(lastPen);
}



void Switcher::OnMouseMoveEvent(int mouseX, int mouseY)
{
	isHover = isMouseHover(mouseX, mouseY);
}

void Switcher::OnMouseLeftBtnPressEvent()
{
	if (!isHover)
	{
		return;
	}

	if (!isDown)
	{
		isDown = true;
		*value = !*value;
	}
}

void Switcher::OnMouseLeftBtnReleaseEvent()
{
	if (isDown)
	{
		isDown = false;
		SoundManager::GetInstance()->PlaySe(Se::buttonClick);
	}
}