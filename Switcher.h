//Switcher.h: ���ؿؼ�����

#pragma once

#include "Widget.h"

#include <qcolor.h>
#include <qwidget.h>

#include <string>

class UiManager;


/**
* Switcher (Widget)
* ����ui�п��ؿؼ�������
* ����һ��bool���ñ���
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