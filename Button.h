//Button.h: 按钮控件类型

#pragma once

#include "Widget.h"

#include <qcolor.h>
#include <qwidget.h>

#include <string>

class UiManager;


/**
* Button (Widget)
* 代表ui中按钮控件的类型
*/
class Button : public Widget
{
	Q_OBJECT

public:
	
	//快捷键
	int hotkey;

	std::string str;



	Button(const std::string& str = "", int hotkey = 0);



	void Draw(QPainter* painter) const override;



	void OnKeyPressEvent(int key) override;

	void OnKeyReleaseEvent(int key) override;

	void OnMouseMoveEvent(int mouseX, int mouseY) override;

	void OnMouseLeftBtnPressEvent() override;

	void OnMouseLeftBtnReleaseEvent() override;

signals:
	
	//按钮被按下时发射
	void ClickSignal();

private:

	bool isDown;

	bool isHover;

	bool hotkeyPressed;

};