//UiManager.h： ui管理器类型

#pragma once

#include <qwidget.h>

#include <list>

class Layout;
class GameManager;



/**
* UiManager (QWidget)
* 管理ui的单例类型
*/
class UiManager : public QWidget
{
	Q_OBJECT

public:

	static UiManager* GetInstance();

	static void ReleaseInstance();



	UiManager();

	~UiManager();



	//进入界面
	void Enter(Layout* layout);

	//返回上一个界面
	void Back();



	//绘制
	void Draw(QPainter* painter) const;

	//将layout添加到绘制列表
	void AddDrawList(Layout* layout);



	void OnKeyPressEvent(int key);

	void OnKeyReleaseEvent(int key);

	void OnMouseMoveEvent(int mouseX, int mouseY);

	void OnMouseLeftBtnPressEvent();

	void OnMouseLeftBtnReleaseEvent();

protected:

	void timerEvent(QTimerEvent* event) override;

private:

	std::list<Layout*> layouts;

	std::list<Layout*> drawList;

	int time;

	int timerId;
};
