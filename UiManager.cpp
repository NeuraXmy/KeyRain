//UiManager.cpp： ui管理器类型

#include "UiManager.h"
#include "Define.h"
#include "Layout.h"
#include "Background.h"

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
	if (instance)
	{
		delete instance;
	}
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
	Background::ReleaseInstance();
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

	Background::GetInstance()->Draw(painter);

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
	//转化为轨道坐标系
	layouts.back()->OnMouseMoveEvent(mouseX - Def::trackPosX, 
		(Def::windowHeight - mouseY) - Def::trackPosY);
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

	for (auto layout : drawList)
	{
		layout->Update(time);
		Background::GetInstance()->Update(time);
	}
}

