//DrawManager.h: 绘图管理器类型

#pragma once

#include <qwidget.h>

/**
* DrawManager (QWidget)
* 控制所有绘图操作的单例类型
*/
class DrawManager : public QWidget
{
	Q_OBJECT

public:

	static DrawManager* GetInstance();

	static void ReleaseInstance();

protected:

	void timerEvent(QTimerEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

private:

	DrawManager();

	~DrawManager();

	int timerId;

};
