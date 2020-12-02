//Layout.h: 界面类

#pragma once

#include <list>

class QPainter;

class Widget;
class UiManager;



/**
* Layout
* 代表一个界面的类型
*/
class Layout
{
public:

	Layout();

	~Layout();



	//进入该界面
	void Enter();

	//退出该界面
	void Exit();
	


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

	int x;
	int y;

	bool visible;

	std::list<Widget*> widgets;

};