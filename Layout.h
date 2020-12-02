//Layout.h: ������

#pragma once

#include <list>

class QPainter;

class Widget;
class UiManager;



/**
* Layout
* ����һ�����������
*/
class Layout
{
public:

	Layout();

	~Layout();



	//����ý���
	void Enter(bool withAnimation = true);

	//�˳��ý���
	void Exit(bool withAnimation = true);
	


	void Update(int time);

	void Draw(QPainter* painter) const;



	void AddWidget(Widget* w);

	void ClearWidget();



	void OnKeyPressEvent(int key);

	void OnKeyReleaseEvent(int key);

	void OnMouseMoveEvent(int mouseX, int mouseY);

	void OnMouseLeftBtnPressEvent();

	void OnMouseLeftBtnReleaseEvent();

private:

	mutable double x;
	mutable double y;

	bool visible;

	std::list<Widget*> widgets;

};