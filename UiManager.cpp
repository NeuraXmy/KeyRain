#include "UiManager.h"
#include "Define.h"
#include "Layout.h"
#include "Ui.h"

#include <qevent.h>
#include <qtimer.h>
#include <qpainter.h>
#include <qdebug.h>

UiManager::UiManager(GameManager* game, QWidget* parent)
	: QWidget(parent)
	, time(0)
{
	this->resize(Def::windowWidth, Def::windowHeight);

	//this->setVisible(false);
	this->setMouseTracking(true);

	timerId = QWidget::startTimer(Def::uiTick, Qt::PreciseTimer);

	Ui::Init(game, this);
}

UiManager::~UiManager()
{

}

void UiManager::Enter(Layout* layout)
{
	if (layouts.size())
	{
		layouts.back()->Exit();
	}
	layouts.push_back(layout);
	layouts.back()->Enter();
}

void UiManager::Back()
{
	if (layouts.size() > 1)
	{
		layouts.back()->Exit();
		layouts.pop_back();
		layouts.back()->Enter();
	}
}

void UiManager::Show(QPainter* painter) const
{
	painter->translate(Def::trackPosX, Def::trackPosY);

	for (auto lay : allLayouts)
	{
		lay->Show(painter);
	}

	painter->translate(-Def::trackPosX, -Def::trackPosY);
}

void UiManager::AddLayout(Layout* layout)
{
	allLayouts.push_back(layout);
}

void UiManager::timerEvent(QTimerEvent* event)
{
	grabKeyboard();
	grabMouse();

	if (event->timerId() != timerId)
	{
		return;
	}

	time += Def::uiTick;

	layouts.back()->Update(time);
}

void UiManager::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		emit MouseLeftPressSignal();
	}
}

void UiManager::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		emit MouseLeftReleaseSignal();
	}
}

void UiManager::mouseMoveEvent(QMouseEvent* event)
{
	emit MouseMoveSignal(event->pos().x(), event->pos().y());
}

void UiManager::keyPressEvent(QKeyEvent* event)
{
	if (event->isAutoRepeat())
	{
		return;
	}

	emit KeyPressSignal(event->key());
}

void UiManager::keyReleaseEvent(QKeyEvent* event)
{
	if (event->isAutoRepeat())
	{
		return;
	}

	emit KeyReleaseSignal(event->key());
}

