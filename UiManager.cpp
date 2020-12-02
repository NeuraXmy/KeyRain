//UiManager.cpp： ui管理器类型

#include "UiManager.h"
#include "Define.h"
#include "Layout.h"

#include <qevent.h>
#include <qtimer.h>
#include <qpainter.h>
#include <qdebug.h>



namespace
{
	UiManager* instance = nullptr;
}

UiManager* UiManager::GetInstance()
{
	if (!instance)
	{
		instance = new UiManager();
	}
	return instance;
}

void UiManager::ReleaseInstance()
{
	delete instance;
}



UiManager::UiManager()
	: QWidget()
	, time(0)
{
	this->hide();

	timerId = QWidget::startTimer(Def::uiTick, Qt::PreciseTimer);
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



void UiManager::Draw(QPainter* painter) const
{
	painter->translate(Def::trackPosX, Def::trackPosY);

	for (auto layout : drawList)
	{
		layout->Draw(painter);
	}

	painter->translate(-Def::trackPosX, -Def::trackPosY);
}

void UiManager::AddDrawList(Layout* layout)
{
	drawList.push_back(layout);
}



void UiManager::OnKeyPressEvent(int key)
{
	layouts.back()->OnKeyPressEvent(key);
}

void UiManager::OnKeyReleaseEvent(int key)
{
	layouts.back()->OnKeyReleaseEvent(key);
}

void UiManager::OnMouseMoveEvent(int mouseX, int mouseY)
{
	qDebug() << mouseX - Def::trackPosX << (Def::windowHeight - mouseY) - (Def::windowHeight - Def::trackPosY - Def::trackHeight);
	layouts.back()->OnMouseMoveEvent(mouseX - Def::trackPosX, 
		(Def::windowHeight - mouseY) - (Def::windowHeight - Def::trackPosY - Def::trackHeight));
}

void UiManager::OnMouseLeftBtnPressEvent()
{
	layouts.back()->OnMouseLeftBtnPressEvent();
}

void UiManager::OnMouseLeftBtnReleaseEvent()
{
	layouts.back()->OnMouseLeftBtnReleaseEvent();
}



void UiManager::timerEvent(QTimerEvent* event)
{
	if (event->timerId() != timerId)
	{
		return;
	}

	time += Def::uiTick;

	layouts.back()->Update(time);
}

