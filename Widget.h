//Widget.h: 控件类型

#pragma once

#include <qobject.h>

class QPainter;



//控件的锚定位置
enum class Anchor
{
	Center,
	LeftBottom
};



/**
* Widget (QObject)
* 代表ui中的控件的抽象接口类型
*/
class Widget : public QObject
{
	Q_OBJECT

public:

	int x;
	int y;

	int w;
	int h;

	//锚定位置(默认为左下)
	Anchor anchor;

	bool visible;

	//是否在当前的界面
	bool inCurrentLayout;



	Widget();
	
	virtual ~Widget();


	virtual void Reset();

	virtual void Update(int time);

	virtual void Draw(QPainter* painter) const;



	virtual void OnKeyPressEvent(int key);

	virtual void OnKeyReleaseEvent(int key);

	virtual void OnMouseMoveEvent(int mouseX, int mouseY);

	virtual void OnMouseLeftBtnPressEvent();

	virtual void OnMouseLeftBtnReleaseEvent();

protected:
	
	//检测鼠标是否在控件上
	bool isMouseHover(int mouseX, int mouseY) const;

};
