//Ui.cpp ui的初始化

#include "Ui.h"
#include "UiManager.h"
#include "GameManager.h"
#include "Layout.h"
#include "Define.h"

#include "Button.h"
#include "Text.h"

#include <qobject.h>

namespace Ui
{
	Layout nullLayout;
	Layout gameLayout;
	Layout pauseLayout;



	//槽行为
	namespace Action
	{
		//ui回退
		void Back()
		{
			UiManager::GetInstance()->Back();
		}
		//跳转到暂停界面
		void EnterPauseLayout()
		{
			UiManager::GetInstance()->Enter(&pauseLayout);
		}
		//游戏暂停
		void GamePause()
		{
			GameManager::GetInstance()->OnPause();
		}
		//游戏继续
		void GameResume()
		{
			GameManager::GetInstance()->OnResume();
		}
	}



	void Init()
	{
		Text* text = new Text("PAUSED", 40, Qt::green);
		text->x = Def::trackWidth / 2, text->y = Def::trackHeight / 2 + 50;
		text->anchor = Anchor::Center;

		Button* resumeBtn = new Button("RESUME", Qt::Key::Key_Escape);
		resumeBtn->x = Def::trackWidth / 2, resumeBtn->y = Def::trackHeight / 2 - 20;
		resumeBtn->w = 160, resumeBtn->h = 40;
		resumeBtn->anchor = Anchor::Center;
		QObject::connect(resumeBtn, &Button::ClickSignal, &Action::Back);
		QObject::connect(resumeBtn, &Button::ClickSignal, &Action::GameResume);

		pauseLayout.AddWidget(text);
		pauseLayout.AddWidget(resumeBtn);


		Button* pauseBtn = new Button("PAUSE", Qt::Key::Key_Escape);
		pauseBtn->visible = false;
		QObject::connect(pauseBtn, &Button::ClickSignal, &Action::EnterPauseLayout);
		QObject::connect(pauseBtn, &Button::ClickSignal, &Action::GamePause);

		gameLayout.AddWidget(pauseBtn);


		UiManager::GetInstance()->AddDrawList(&nullLayout);
		UiManager::GetInstance()->AddDrawList(&pauseLayout);
		UiManager::GetInstance()->AddDrawList(&gameLayout);
	}
}
