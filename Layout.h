#pragma once

#include <list>

class QPainter;

class Widget;
class UiManager;

class Layout
{
public:

	Layout();

	~Layout();

	void Enter();

	void Exit();

	void Update(int time);

	void Show(QPainter* painter) const;

	void AddWidget(Widget* w);

	void ClearWidget();

private:

	int x;
	int y;

	bool visible;

	std::list<Widget*> widgets;

};