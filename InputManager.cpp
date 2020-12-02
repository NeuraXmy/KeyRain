//InputManager.cpp: �������������

#include "InputManager.h"
#include "DrawManager.h"
#include "Define.h"

#include <qdebug.h>

namespace
{
	InputManager* instance = nullptr;
}

InputManager* InputManager::GetInstance()
{
	if (!instance)
	{
		instance = new InputManager();
	}
	return instance;
}

void InputManager::ReleaseInstance()
{
	delete instance;
}



InputManager::InputManager()
	: QWidget()
{
	timerId = QWidget::startTimer(Def::inputTickTime, Qt::PreciseTimer);

	this->setMouseTracking(true);

	this->hide();
}

InputManager::~InputManager()
{
	
}



void InputManager::timerEvent(QTimerEvent* event)
{
	if (event->timerId() != timerId)
	{
		return;
	}
	grabKeyboard();
	grabMouse();
}

void InputManager::mouseMoveEvent(QMouseEvent* event)
{
	QPoint pos = DrawManager::GetInstance()->mapFromGlobal(event->globalPos());
	emit MouseMoveSignal(pos.x(), pos.y());
}

void InputManager::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		emit MouseLeftBtnPressSignal();
	}
	if (event->button() == Qt::MouseButton::RightButton)
	{
		emit MouseRightBtnPressSignal();
	}
}

void InputManager::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		emit MouseLeftBtnReleaseSignal();
	}
	if (event->button() == Qt::MouseButton::RightButton)
	{
		emit MouseRightBtnReleaseSignal();
	}
}

void InputManager::keyPressEvent(QKeyEvent* event)
{
	if (event->isAutoRepeat())
	{
		return;
	}
	emit KeyPressSignal(event->key());
}

void InputManager::keyReleaseEvent(QKeyEvent* event)
{
	if (event->isAutoRepeat())
	{
		return;
	}
	emit KeyReleaseSignal(event->key());
}
