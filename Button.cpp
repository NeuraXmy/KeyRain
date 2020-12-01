#include "Button.h"
#include "Define.h"
#include "UiManager.h"

#include <qpainter.h>

Button::Button(UiManager* mgr, const std::string& str, int hotkey)
	: Widget()
	, mgr(mgr)
	, str(str)
	, isDown(false)
	, isHover(false)
	, hotkey(hotkey)
	, hotkeyPressed(false)

{
	connect(mgr, &UiManager::MouseMoveSignal, this, &Button::OnMouseMove);
	connect(mgr, &UiManager::MouseLeftPressSignal, this, &Button::OnMouseLeftPress);
	connect(mgr, &UiManager::MouseLeftReleaseSignal, this, &Button::OnMouseLeftRelease);
	connect(mgr, &UiManager::KeyPressSignal, this, &Button::OnKeyPress);
	connect(mgr, &UiManager::KeyReleaseSignal, this, &Button::OnKeyRelease);
}

void Button::Update(int time)
{

}

void Button::OnMouseMove(int mouseX, int mouseY)
{
	isHover = isMouseHover(mouseX, mouseY);
}

void Button::OnMouseLeftPress()
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

void Button::OnMouseLeftRelease()
{
	if (isDown)
	{
		isDown = false;
		if (isHover)
		{
			emit ClickSignal();
		}
	}
}

void Button::OnKeyPress(int key)
{
	if (key == hotkey && !isDown && !hotkeyPressed)
	{
		hotkeyPressed = true;
		isDown = true;

		emit ClickSignal();
	}
}

void Button::OnKeyRelease(int key)
{
	if (key == hotkey && isDown &&  hotkeyPressed)
	{
		hotkeyPressed = false;
		isDown = false;
	}
}


void Button::Show(QPainter* painter) const
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
		painter->translate(w/ 2 - x, h / 2 - y);
}
