//Application.cpp: 应用程序主体类

#include "Application.h"
#include "Define.h"

#include "GameManager.h"
#include "InputManager.h"
#include "UiManager.h"
#include "ParticleManager.h"
#include "DrawManager.h"

#include <qdatetime.h>
#include <qfontdatabase.h>
#include <qapplication.h>
#include <qdebug.h>

namespace
{
	Application* instance;
}

Application* Application::GetInstance()
{
	if (!instance)
	{
		instance = new Application();
	}
	return instance;
}

void Application::ReleaseInstance()
{
	delete instance;
}



Application::Application()
	: QWidget()
{
	Def::SetRandSeed(QDateTime::currentDateTime().time().msec());

	//加载字体
	{
		int fontId = QFontDatabase::addApplicationFont((Def::resPath + "font/Freon.ttf").c_str());
		QStringList fontIDs = QFontDatabase::applicationFontFamilies(fontId);
		if (!fontIDs.isEmpty())
		{
			QFont font(fontIDs.first());
			QApplication::setFont(font);
		}
		else
		{
			qDebug() << "[ERR] Failed to load font";
		}
	}

	InitSingalSlots();
}

Application::~Application()
{
	GameManager::ReleaseInstance();
	InputManager::ReleaseInstance();
	ParticleManager::ReleaseInstance();
}



void Application::InitSingalSlots()
{
	connect(InputManager::GetInstance(), &InputManager::KeyPressSignal, 
		GameManager::GetInstance(), &GameManager::OnKeyPressEvent);
	connect(InputManager::GetInstance(), &InputManager::KeyReleaseSignal,
		GameManager::GetInstance(), &GameManager::OnKeyReleaseEvent);
}

void Application::Start()
{
	GameManager::GetInstance()->show();
	GameManager::GetInstance()->Start("cppkeywords");
}
