//DrawManager.cpp: 绘图管理器类型

#include "DrawManager.h"
#include "Define.h"
#include "Standing.h"

#include "GameManager.h"
#include "ParticleManager.h"
#include "UiManager.h"

#include <qpainter.h>
#include <qevent.h>
#include <qicon.h>



namespace
{
	DrawManager* instance = nullptr;
}

DrawManager* DrawManager::GetInstance()
{
	if (!instance)
	{
		instance = new DrawManager();
	}
	return instance;
}

void DrawManager::ReleaseInstance()
{
	delete instance;
}



DrawManager::DrawManager()
	: QWidget()
{
	timerId = startTimer(Def::frameTime, Qt::PreciseTimer);

	QIcon icon((Def::resPath + "icon.ico").c_str());

	this->setWindowIcon(icon);

	this->setFixedSize(Def::windowWidth, Def::windowHeight);
	this->show();
}

DrawManager::~DrawManager()
{
	
}



void DrawManager::timerEvent(QTimerEvent* event)
{
	if (timerId != event->timerId())
	{
		return;
	}
	this->repaint();
}

void DrawManager::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	//将qt的右上坐标系转换为左下坐标系
	painter.scale(1.0, -1.0);
	painter.translate(0, -Def::windowHeight);

	GameManager::GetInstance()->DrawTrack(&painter);

	if (GameManager::GetInstance()->GetStat() == GameStat::running)
	{
		ParticleManager::GetInstacne()->Draw(&painter);
	}

	UiManager::GetInstance()->Draw(&painter);

	GameManager::GetInstance()->DrawGui(&painter);

}

void DrawManager::closeEvent(QCloseEvent* event)
{
	Standing::GetInstance()->SaveRecord();
	emit WindowCloseSignal();
}


