//Switcher.h: 开关控件类型

#pragma once

#include "Widget.h"

#include <qcolor.h>
#include <qwidget.h>

#include <string>

class UiManager;


/**
* Switcher (Widget)
* 代表ui中开关控件的类型
* 控制一个bool设置变量
*/
class Switcher final : public Widget
{
	Q_OBJECT

public:

	Switcher(bool* value);


	void Reset() override;

	void Draw(QPainter* painter) const override;



	void OnMouseMoveEvent(int mouseX, int mouseY) override;

	void OnMouseLeftBtnPressEvent() override;

	void OnMouseLeftBtnReleaseEvent() override;

private:

	bool isDown;

	bool isHover;

	bool* value;

};