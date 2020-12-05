//SlideBar.h: 拖动条控件类型

#pragma once

#include "Widget.h"

#include <qcolor.h>
#include <qwidget.h>

#include <string>

class UiManager;


/**
* SlideBar (Widget)
* 代表ui中拖动条控件的类型
* 控制一个double设置变量
*/
class SlideBar final : public Widget
{
	Q_OBJECT

public:

	SlideBar(double* value, double minVal, double maxVal);


	void Reset() override;

	void Draw(QPainter* painter) const override;


	void OnMouseMoveEvent(int mouseX, int mouseY) override;

	void OnMouseLeftBtnPressEvent() override;

	void OnMouseLeftBtnReleaseEvent() override;

private:

	bool isDown;

	bool isHover;

	double* value;

	double minVal;

	double maxVal;

};
