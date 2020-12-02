//Button.h: 按钮控件类型

#include "Button.h"
#include "Define.h"

#include <qpainter.h>



Button::Button(const std::string& str, int hotkey)
	: Widget()
	, str(str)
	, isDown(false)
	, isHover(false)
	, hotkey(hotkey)
	, hotkeyPressed(false)

{
	
}



void Button::Draw(QPainter* painter) const
{
	if (!visible)
	{
		return;
	}

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
}



void Button::OnMouseMoveEvent(int mouseX, int mouseY)
{
	isHover = isMouseHover(mouseX, mouseY);
}

void Button::OnMouseLeftBtnPressEvent()
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

void Button::OnMouseLeftBtnReleaseEvent()
{
	if (isDown)
	{
		isDown = false;
		//鼠标放开时在按钮上就判断按钮正常按下
		//不在按钮上则不判断按下
		if (isHover)
		{
			emit ClickSignal();
		}
	}
}

void Button::OnKeyPressEvent(int key)
{
	if (key == hotkey && !isDown && !hotkeyPressed)
	{
		hotkeyPressed = true;
		isDown = true;

		//快捷键按下时即马上判断按钮按下
		emit ClickSignal();
	}
}

void Button::OnKeyReleaseEvent(int key)
{
	if (key == hotkey && isDown &&  hotkeyPressed)
	{
		hotkeyPressed = false;
		isDown = false;
	}
}


