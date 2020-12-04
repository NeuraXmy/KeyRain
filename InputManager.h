//InputManager.h: 输入管理器类型

#pragma once

#include <qwidget.h>
#include <qevent.h>

/**
* InputManager (QWidget)
* 用于管理键盘与鼠标输入的单例类型
*/
class InputManager final : public QWidget
{
	Q_OBJECT

public:

	static InputManager* GetInstance();

	static void ReleaseInstance();

signals:

	void MouseMoveSignal(int mouseX, int mouseY);

	void MouseLeftBtnPressSignal();

	void MouseLeftBtnReleaseSignal();

	void MouseRightBtnPressSignal();

	void MouseRightBtnReleaseSignal();

	void KeyPressSignal(int key);

	void KeyReleaseSignal(int key);

protected:

	void timerEvent(QTimerEvent* event) override;

	void mouseMoveEvent(QMouseEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;

	void mouseReleaseEvent(QMouseEvent* event) override;

	void keyPressEvent(QKeyEvent* event) override;

	void keyReleaseEvent(QKeyEvent* event) override;

private:

	int timerId;

	InputManager();

	~InputManager();

};