//Button.h: ��ť�ؼ�����

#pragma once

#include "Widget.h"

#include <qcolor.h>
#include <qwidget.h>

#include <string>

class UiManager;


/**
* Button (Widget)
* ����ui�а�ť�ؼ�������
*/
class Button : public Widget
{
	Q_OBJECT

public:
	
	//��ݼ�
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
	
	//��ť������ʱ����
	void ClickSignal();

private:

	bool isDown;

	bool isHover;

	bool hotkeyPressed;

};