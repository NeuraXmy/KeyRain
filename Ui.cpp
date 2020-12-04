//Ui.cpp ui�ĳ�ʼ��

#include "Application.h"

#include "Ui.h"
#include "UiManager.h"
#include "GameManager.h"
#include "Layout.h"
#include "Define.h"
#include "Standing.h"
#include "Settings.h"

#include "Button.h"
#include "Text.h"
#include "RecordList.h"
#include "Image.h"

#include <qobject.h>
#include <fstream>
#include <qdebug.h>

namespace Ui
{
	Layout nullLayout;
	Layout mainMenuLayout;
	Layout gameLayout;
	Layout pauseLayout;
	Layout gameOverLayout;
	Layout selectLevelLayout;
	Layout aboutsLayout;
	Layout standingLayout;
	Layout settingsLayout;

	RecordList* levelList;
	RecordList* standingRankList;
	RecordList* standingScoreList;
	RecordList* standingLevelNameList;
	RecordList* standingTimeList;

	Text* ggScoreText;
	Text* ggLevelNameText;

	std::vector<std::string> levelPaths;

	//����Ϊ
	namespace Action
	{
		//����
		void Back()
		{
			UiManager::GetInstance()->Back();
		}

		//��Ϸ��ͣ
		void GamePause()
		{
			if (GameManager::GetInstance()->GetStat() == GameStat::running)
			{
				GameManager::GetInstance()->OnPause();
				//��ת����ͣ����
				UiManager::GetInstance()->Enter(&pauseLayout);
			}
		}

		//��Ϸ����
		void GameResume()
		{
			if (GameManager::GetInstance()->GetStat() == GameStat::paused)
			{
				GameManager::GetInstance()->OnResume();
				//���˵���Ϸ����
				UiManager::GetInstance()->Back();
			}
		}

		//��Ϸ�˳�
		void GameExit()
		{
			//��Ϸ����
			GameManager::GetInstance()->OnExit();
			//�˻���Ϸ����
			UiManager::GetInstance()->Back();
			//�˻�ѡ�ؽ���
			UiManager::GetInstance()->Back();
			//�˻�������
			UiManager::GetInstance()->Back();
		}

		//��Ϸ����
		void GameOver(GameRecord record)
		{
			//�˻�ѡ�ؽ���
			UiManager::GetInstance()->Back();
			//�˻�������
			UiManager::GetInstance()->Back();
			//���ý�����������
			ggLevelNameText->SetStr(record.levelName);
			ggScoreText->SetStr(std::to_string(record.score));
			//������������
			UiManager::GetInstance()->Enter(&gameOverLayout);
		}

		//��ת��ѡ�ؽ���
		void EnterSelectLevel()
		{
			UiManager::GetInstance()->Enter(&selectLevelLayout);
			//���عؿ��б�
			{
				std::string path = Def::resPath + "level/level_list.list";
				std::fstream in(path);
				if (!in)
				{
					qDebug() << "[ERR] Failed to load level list";
					return;
				}

				int levelCount = 0;
				in >> levelCount;
				in.get();

				for (int i = 0; i < levelCount; i++)
				{
					std::string name, file;
					std::getline(in, file);
					std::getline(in, name);
					levelList->AddRecord(name);
					levelPaths.push_back(file);
				}

				if (!in)
				{
					levelPaths.clear();
					levelList->Clear();
				}
				in.close();
			}
		}

		//��ת�����ڽ���
		void EnterAbouts()
		{
			UiManager::GetInstance()->Enter(&aboutsLayout);
		}

		//��ת����������
		void EnterStanding()
		{
			UiManager::GetInstance()->Enter(&standingLayout);
			//��������
			{
				auto records = Standing::GetInstance()->GetRecord();
				for (auto record : records)
				{
					standingRankList->AddRecord(std::to_string(record.rank));
					standingScoreList->AddRecord(std::to_string(record.score));
					standingLevelNameList->AddRecord(record.levelName);
					standingTimeList->AddRecord(record.time);
				}
			}
		}

		//��Ϸ��ʼ
		void StartGame()
		{	
			if (levelPaths.size())
			{
				if (GameManager::GetInstance()->OnStart(levelPaths[levelList->GetCurrentIndex()]))
				{
					UiManager::GetInstance()->Enter(&gameLayout);
				}
			}
		}

		//�������
		void Exit()
		{
			Application::GetInstance()->Exit();
		}

		//��ת�����ý���
		void EnterSettings()
		{
			UiManager::GetInstance()->Enter(&settingsLayout);
		}

		//��������
		void SaveSettings()
		{
			Settings::GetInstance()->Save();
			UiManager::GetInstance()->Back();
		}

		//ȡ������
		void CancelSettings()
		{
			Settings::GetInstance()->Load();
			UiManager::GetInstance()->Back();
		}
	}



	void Init()
	{
		//-------------------------------------���˵�------------------------------------//

		{
			//��ʼ��Ϸ��ť
			Button* startBtn = new Button("START", Qt::Key::Key_Return);
			startBtn->x = Def::trackWidth / 2, startBtn->y = Def::trackHeight / 2;
			startBtn->w = 200, startBtn->h = 40;
			startBtn->anchor = Anchor::Center;
			QObject::connect(startBtn, &Button::ClickSignal, &Action::EnterSelectLevel);

			//��¼��ť
			Button* recordBtn = new Button("RECORD");
			recordBtn->x = Def::trackWidth / 2, recordBtn->y = Def::trackHeight / 2 - 50;
			recordBtn->w = 180, recordBtn->h = 35;
			recordBtn->anchor = Anchor::Center;
			QObject::connect(recordBtn, &Button::ClickSignal, &Action::EnterStanding);

			//���ð�ť
			Button* settingsBtn = new Button("SETTINGS");
			settingsBtn->x = Def::trackWidth / 2, settingsBtn->y = Def::trackHeight / 2 - 90;
			settingsBtn->w = 180, settingsBtn->h = 35;
			settingsBtn->anchor = Anchor::Center;
			QObject::connect(settingsBtn, &Button::ClickSignal, &Action::EnterSettings);

			//���ڰ�ť
			Button* aboutBtn = new Button("ABOUT");
			aboutBtn->x = Def::trackWidth / 2, aboutBtn->y = Def::trackHeight / 2 - 130;
			aboutBtn->w = 180, aboutBtn->h = 35;
			aboutBtn->anchor = Anchor::Center;
			QObject::connect(aboutBtn, &Button::ClickSignal, &Action::EnterAbouts);

			//������ť
			Button* exitBtn = new Button("EXIT", Qt::Key::Key_Escape);
			exitBtn->x = Def::trackWidth / 2, exitBtn->y = Def::trackHeight / 2 - 180;
			exitBtn->w = 180, exitBtn->h = 35;
			exitBtn->anchor = Anchor::Center;
			QObject::connect(exitBtn, &Button::ClickSignal, &Action::Exit);

			//����
			Image* title = new Image(Def::resPath + "tex/title.png");
			title->x = Def::trackWidth * 0.5, title->y = Def::trackHeight * 0.7;
			title->w = Def::trackWidth * 0.7, title->h = 100;
			title->anchor = Anchor::Center;

			mainMenuLayout.AddWidget(startBtn);
			mainMenuLayout.AddWidget(exitBtn);
			mainMenuLayout.AddWidget(settingsBtn);
			mainMenuLayout.AddWidget(recordBtn);
			mainMenuLayout.AddWidget(aboutBtn);
			mainMenuLayout.AddWidget(title);
		}

		//-----------------------------------ѡ�ؽ���-----------------------------------//

		{
			//����
			Text* text = new Text("SELECT DICTIONARY", 40, Qt::green);
			text->x = Def::trackWidth / 2, text->y = Def::trackHeight * 0.8;
			text->anchor = Anchor::Center;

			//���ϰ�ť
			Button* upBtn = new Button("UP", Qt::Key::Key_Up);
			upBtn->x = Def::trackWidth * 0.75, upBtn->y = Def::trackHeight / 2 - 60 + 120;
			upBtn->w = 100, upBtn->h = 35;
			upBtn->anchor = Anchor::Center;

			//���°�ť
			Button* downBtn = new Button("DOWN", Qt::Key::Key_Down);
			downBtn->x = Def::trackWidth * 0.75, downBtn->y = Def::trackHeight / 2 - 60 - 120;
			downBtn->w = 100, downBtn->h = 35;
			downBtn->anchor = Anchor::Center;

			//ѡ���б�
			levelList = new RecordList(5);
			levelList->x = Def::trackWidth * 0.75, levelList->y = Def::trackHeight / 2 - 60;
			levelList->w = Def::trackWidth * 0.5, levelList->h = Def::trackHeight * 0.3;
			levelList->BindDownButton(downBtn);
			levelList->BindUpButton(upBtn);
			levelList->anchor = Anchor::Center;

			//���ذ�ť
			Button* backBtn = new Button("BACK", Qt::Key::Key_Escape);
			backBtn->x = 10, backBtn->y = 10;
			backBtn->w = 100, backBtn->h = 30;
			backBtn->anchor = Anchor::LeftBottom;
			QObject::connect(backBtn, &Button::ClickSignal, &Action::Back);

			//��ʼ��Ϸ��ť
			Button* startBtn = new Button("START", Qt::Key::Key_Return);
			startBtn->x = 110, startBtn->y = Def::trackHeight / 2 - 40;
			startBtn->w = 140, startBtn->h = 40;
			startBtn->anchor = Anchor::Center;
			QObject::connect(startBtn, &Button::ClickSignal, &Action::StartGame);

			selectLevelLayout.AddWidget(text);
			selectLevelLayout.AddWidget(levelList);
			selectLevelLayout.AddWidget(downBtn);
			selectLevelLayout.AddWidget(backBtn);
			selectLevelLayout.AddWidget(upBtn);
			selectLevelLayout.AddWidget(startBtn);
		}

		//-----------------------------------��ͣ����-----------------------------------//

		{
			//��ͣ����
			Text* text = new Text("PAUSED", 45, Qt::yellow);
			text->x = Def::trackWidth / 2, text->y = Def::trackHeight / 2 + 50;
			text->anchor = Anchor::Center;

			//�ָ���ť
			Button* resumeBtn = new Button("RESUME", Qt::Key::Key_Escape);
			resumeBtn->x = Def::trackWidth / 2, resumeBtn->y = Def::trackHeight / 2 - 40;
			resumeBtn->w = 160, resumeBtn->h = 35;
			resumeBtn->anchor = Anchor::Center;
			QObject::connect(resumeBtn, &Button::ClickSignal, &Action::GameResume);

			//�˳���ť
			Button* exitBtn = new Button("EXIT");
			exitBtn->x = Def::trackWidth / 2, exitBtn->y = Def::trackHeight / 2 - 100;
			exitBtn->w = 160, exitBtn->h = 35;
			exitBtn->anchor = Anchor::Center;
			QObject::connect(exitBtn, &Button::ClickSignal, &Action::GameExit);

			pauseLayout.AddWidget(text);
			pauseLayout.AddWidget(resumeBtn);
			pauseLayout.AddWidget(exitBtn);
		}

		//-----------------------------------��Ϸ����-----------------------------------//

		{
			//��ͣ��ť�����أ�
			Button* pauseBtn = new Button("PAUSE", Qt::Key::Key_Escape);
			pauseBtn->visible = false;
			QObject::connect(pauseBtn, &Button::ClickSignal, &Action::GamePause);

			gameLayout.AddWidget(pauseBtn);
		}

		//---------------------------------��Ϸ��������---------------------------------//

		{
			//��Ϸ��������
			Text* text = new Text("GAME OVER", 50, Qt::red);
			text->x = Def::trackWidth / 2, text->y = Def::trackHeight / 2 + 100;
			text->anchor = Anchor::Center;

			Text* nameText = new Text("[ DICTIONARY ]", 25, Qt::green);
			nameText->x = Def::trackWidth / 2, nameText->y = 270;
			nameText->anchor = Anchor::Center;

			ggLevelNameText = new Text("LEVEL NAME", 30, Qt::yellow);
			ggLevelNameText->x = Def::trackWidth / 2, ggLevelNameText->y = 230;
			ggLevelNameText->anchor = Anchor::Center;

			Text* scoreText = new Text("[ YOUR SCORE ]", 25, Qt::green);
			scoreText->x = Def::trackWidth / 2, scoreText->y = 180;
			scoreText->anchor = Anchor::Center;

			ggScoreText = new Text("SCORE", 40, Qt::yellow);
			ggScoreText->x = Def::trackWidth / 2, ggScoreText->y = 130;
			ggScoreText->anchor = Anchor::Center;

			//���ذ�ť
			Button* okBtn = new Button("BACK", Qt::Key::Key_Escape);
			okBtn->x = Def::trackWidth / 2, okBtn->y = 50;
			okBtn->w = 160, okBtn->h = 35;
			okBtn->anchor = Anchor::Center;
			QObject::connect(okBtn, &Button::ClickSignal, &Action::Back);

			gameOverLayout.AddWidget(text);
			gameOverLayout.AddWidget(nameText);
			gameOverLayout.AddWidget(ggLevelNameText);
			gameOverLayout.AddWidget(ggScoreText);
			gameOverLayout.AddWidget(scoreText);
			gameOverLayout.AddWidget(okBtn);

			QObject::connect(GameManager::GetInstance(), &GameManager::GameOverSignal, &Action::GameOver);
		}

		//-------------------------------------���ڽ���----------------------------------//

		{
			//���ذ�ť
			Button* backBtn = new Button("BACK", Qt::Key::Key_Escape);
			backBtn->x = 10, backBtn->y = 10;
			backBtn->w = 100, backBtn->h = 30;
			backBtn->anchor = Anchor::LeftBottom;
			QObject::connect(backBtn, &Button::ClickSignal, &Action::Back);

			//abouts��Ϣ
			Image* about = new Image(Def::resPath + "tex/abouts.png");
			about->w = Def::trackWidth, about->h = Def::trackHeight * 0.9;
			about->anchor = Anchor::LeftBottom;

			aboutsLayout.AddWidget(backBtn);
			aboutsLayout.AddWidget(about);
		}

		//-------------------------------------��������----------------------------------//

		{
			//���ذ�ť
			Button* backBtn = new Button("BACK", Qt::Key::Key_Escape);
			backBtn->x = 10, backBtn->y = 10;
			backBtn->w = 100, backBtn->h = 30;
			backBtn->anchor = Anchor::LeftBottom;
			QObject::connect(backBtn, &Button::ClickSignal, &Action::Back);

			//���ϰ�ť
			Button* upBtn = new Button("UP", Qt::Key::Key_Up);
			upBtn->x = 200, upBtn->y = 10;
			upBtn->w = 100, upBtn->h = 35;
			backBtn->anchor = Anchor::LeftBottom;

			//���°�ť
			Button* downBtn = new Button("DOWN", Qt::Key::Key_Down);
			downBtn->x = 350, downBtn->y = 10;
			downBtn->w = 100, downBtn->h = 35;
			backBtn->anchor = Anchor::LeftBottom;

			//������Ϣ
			standingRankList = new RecordList(15);
			standingRankList->x = 5, standingRankList->y = 70;
			standingRankList->w = Def::trackWidth * 0.9, standingRankList->h = Def::trackHeight * 0.6;
			standingRankList->anchor = Anchor::LeftBottom;
			standingRankList->BindDownButton(downBtn);
			standingRankList->BindUpButton(upBtn);

			//������Ϣ
			standingScoreList = new RecordList(15);
			standingScoreList->x = 50, standingScoreList->y = 70;
			standingScoreList->w = Def::trackWidth * 0.9, standingScoreList->h = Def::trackHeight * 0.6;
			standingScoreList->anchor = Anchor::LeftBottom;
			standingScoreList->BindDownButton(downBtn);
			standingScoreList->BindUpButton(upBtn);

			//�ؿ�����Ϣ
			standingLevelNameList = new RecordList(15);
			standingLevelNameList->x = 150, standingLevelNameList->y = 70;
			standingLevelNameList->w = Def::trackWidth * 0.9, standingLevelNameList->h = Def::trackHeight * 0.6;
			standingLevelNameList->anchor = Anchor::LeftBottom;
			standingLevelNameList->BindDownButton(downBtn);
			standingLevelNameList->BindUpButton(upBtn);

			//ʱ����Ϣ
			standingTimeList = new RecordList(15);
			standingTimeList->x = 310, standingTimeList->y = 70;
			standingTimeList->w = Def::trackWidth * 0.9, standingTimeList->h = Def::trackHeight * 0.6;
			standingTimeList->anchor = Anchor::LeftBottom;
			standingTimeList->BindDownButton(downBtn);
			standingTimeList->BindUpButton(upBtn);

			standingLayout.AddWidget(standingRankList);
			standingLayout.AddWidget(standingScoreList);
			standingLayout.AddWidget(standingLevelNameList);
			standingLayout.AddWidget(standingTimeList);
			standingLayout.AddWidget(downBtn);
			standingLayout.AddWidget(upBtn);
			standingLayout.AddWidget(backBtn);
		}

		//-----------------------------------���ý���-----------------------------------//

		{
			//����
			Text* text = new Text("SETTINGS", 40, Qt::green);
			text->x = Def::trackWidth / 2, text->y = Def::trackHeight * 0.8;
			text->anchor = Anchor::Center;

			//ȡ����ť
			Button* cancelBtn = new Button("CANCEL", Qt::Key::Key_Escape);
			cancelBtn->x = Def::trackWidth * 0.25, cancelBtn->y = 30;
			cancelBtn->w = 140, cancelBtn->h = 30;
			cancelBtn->anchor = Anchor::Center;
			QObject::connect(cancelBtn, &Button::ClickSignal, &Action::CancelSettings);

			//���水ť
			Button* saveBtn = new Button("SAVE", Qt::Key::Key_Return);
			saveBtn->x = Def::trackWidth * 0.75, saveBtn->y = 30;
			saveBtn->w = 140, saveBtn->h = 30;
			saveBtn->anchor = Anchor::Center;
			QObject::connect(saveBtn, &Button::ClickSignal, &Action::SaveSettings);

			settingsLayout.AddWidget(text);
			settingsLayout.AddWidget(cancelBtn);
			settingsLayout.AddWidget(saveBtn);
		}

		//-----------------------------------------------------------------------------//

		//��ӵ�ui�������Ļ�ͼ�б�
		UiManager::GetInstance()->AddDrawList(&nullLayout);
		UiManager::GetInstance()->AddDrawList(&pauseLayout);
		UiManager::GetInstance()->AddDrawList(&gameLayout);
		UiManager::GetInstance()->AddDrawList(&gameOverLayout);
		UiManager::GetInstance()->AddDrawList(&mainMenuLayout);
		UiManager::GetInstance()->AddDrawList(&selectLevelLayout);
		UiManager::GetInstance()->AddDrawList(&aboutsLayout);
		UiManager::GetInstance()->AddDrawList(&standingLayout);
		UiManager::GetInstance()->AddDrawList(&settingsLayout);

		UiManager::GetInstance()->Enter(&mainMenuLayout);
	}
}
