#pragma once
#pragma once
#include "Widget.h"

#include <qcolor.h>
#include <qwidget.h>

#include <string>

class UiManager;

class Button : public Widget
{
	Q_OBJECT

public:
	
	int hotkey;

	std::string str;

	Button(UiManager* mgr, const std::string& str = "", int hotkey = 0);

	void Update(int time) override;

	void Show(QPainter* painter) const override;



	void OnMouseMove(int mouseX, int mouseY);

	void OnMouseLeftPress();

	void OnMouseLeftRelease();

	void OnKeyPress(int key);

	void OnKeyRelease(int key);

signals:
	
	void ClickSignal();

private:

	UiManager* mgr;

	bool isDown;

	bool isHover;

	bool hotkeyPressed;

};