//Application.cpp: 应用程序主体类

#include "Application.h"
#include "Define.h"

#include "GameManager.h"
#include "InputManager.h"
#include "UiManager.h"
#include "ParticleManager.h"
#include "DrawManager.h"

#include "Ui.h"

#include <qdatetime.h>
#include <qfontdatabase.h>
#include <qapplication.h>
#include <qdebug.h>

namespace
{
	Application* instance = nullptr;
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
	this->hide();

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
	DrawManager::ReleaseInstance();
	UiManager::ReleaseInstance();
}



void Application::InitSingalSlots()
{
	connect(InputManager::GetInstance(), &InputManager::KeyPressSignal, 
		GameManager::GetInstance(), &GameManager::OnKeyPressEvent);
	connect(InputManager::GetInstance(), &InputManager::KeyReleaseSignal,
		GameManager::GetInstance(), &GameManager::OnKeyReleaseEvent);
	
	connect(InputManager::GetInstance(), &InputManager::KeyPressSignal,
		UiManager::GetInstance(), &UiManager::OnKeyPressEvent);
	connect(InputManager::GetInstance(), &InputManager::KeyReleaseSignal,
		UiManager::GetInstance(), &UiManager::OnKeyReleaseEvent);
	connect(InputManager::GetInstance(), &InputManager::MouseMoveSignal,
		UiManager::GetInstance(), &UiManager::OnMouseMoveEvent);
	connect(InputManager::GetInstance(), &InputManager::MouseLeftBtnPressSignal,
		UiManager::GetInstance(), &UiManager::OnMouseLeftBtnPressEvent);
	connect(InputManager::GetInstance(), &InputManager::MouseLeftBtnReleaseSignal,
		UiManager::GetInstance(), &UiManager::OnMouseLeftBtnReleaseEvent);
}

void Application::Start()
{
	//实例化绘图管理器
	DrawManager::GetInstance();

	//初始化ui
	Ui::Init();
	UiManager::GetInstance()->Enter(&Ui::gameLayout);

	GameManager::GetInstance()->OnStart("cppkeywords");
}
