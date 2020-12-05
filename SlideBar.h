//SlideBar.h: �϶����ؼ�����

#pragma once

#include "Widget.h"

#include <qcolor.h>
#include <qwidget.h>

#include <string>

class UiManager;


/**
* SlideBar (Widget)
* ����ui���϶����ؼ�������
* ����һ��double���ñ���
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
