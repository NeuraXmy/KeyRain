#pragma once

#include <qwidget.h>

#include <list>

class Layout;
class GameManager;

class UiManager : public QWidget
{
	Q_OBJECT

public:

	UiManager(GameManager* game, QWidget* parent = nullptr);

	~UiManager();

	void Enter(Layout* layout);

	void Back();

	void Show(QPainter* painter) const;

	void AddLayout(Layout* layout);

signals:

	void MouseMoveSignal(int mouseX, int mouseY);

	void MouseLeftPressSignal();

	void MouseLeftReleaseSignal();

	void KeyPressSignal(int key);

	void KeyReleaseSignal(int key);

protected:

	void timerEvent(QTimerEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;

	void mouseReleaseEvent(QMouseEvent* event) override;

	void mouseMoveEvent(QMouseEvent* event) override;

	void keyPressEvent(QKeyEvent* event) override;

	void keyReleaseEvent(QKeyEvent* event) override;

private:

	std::list<Layout*> layouts;

	std::list<Layout*> allLayouts;

	int time;

	int timerId;
};
