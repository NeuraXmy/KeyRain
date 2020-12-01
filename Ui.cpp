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

	UiManager* mgr;
	GameManager* game;

	namespace Action
	{
		void Back()
		{
			mgr->Back();
		}
		void JumpToPauseLayout()
		{
			mgr->Enter(&pauseLayout);
		}
	}

	void Init(GameManager* game, UiManager* mgr)
	{
		Ui::mgr = mgr;
		Ui::game = game;

		Text* text = new Text("PAUSED", 50, Qt::green);
		text->x = Def::trackWidth / 2, text->y = Def::trackHeight / 2 + 50;
		text->anchor = Anchor::Center;

		Button* resumeBtn = new Button(mgr, "RESUME", Qt::Key::Key_Escape);
		resumeBtn->x = Def::trackWidth / 2, resumeBtn->y = Def::trackHeight / 2 - 20;
		resumeBtn->w = 200, resumeBtn->h = 40;
		resumeBtn->anchor = Anchor::Center;
		QObject::connect(resumeBtn, &Button::ClickSignal, &Action::Back);

		pauseLayout.AddWidget(text);
		pauseLayout.AddWidget(resumeBtn);


		Button* pauseBtn = new Button(mgr, "PAUSE", Qt::Key::Key_Escape);
		pauseBtn->visible = false;
		QObject::connect(pauseBtn, &Button::ClickSignal, &Action::JumpToPauseLayout);

		gameLayout.AddWidget(pauseBtn);


		mgr->AddLayout(&nullLayout);
		mgr->AddLayout(&pauseLayout);
		mgr->AddLayout(&gameLayout);
	}
}
