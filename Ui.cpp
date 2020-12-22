//Ui.cpp ui的初始化

#include "Application.h"

#include "Ui.h"
#include "UiManager.h"
#include "GameManager.h"
#include "Layout.h"
#include "Define.h"
#include "Standing.h"
#include "Settings.h"
#include "Background.h"

#include "Button.h"
#include "Text.h"
#include "RecordList.h"
#include "Image.h"
#include "Switcher.h"
#include "SlideBar.h"

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

	//槽行为
	namespace Action
	{
		//返回
		void Back()
		{
			UiManager::GetInstance()->Back();
		}

		//游戏暂停
		void GamePause()
		{
			if (GameManager::GetInstance()->GetStat() == GameStat::running)
			{
				GameManager::GetInstance()->OnPause();
				//跳转到暂停界面
				UiManager::GetInstance()->Enter(&pauseLayout);
				//显示背景
				Background::GetInstance()->Show();
			}
		}

		//游戏继续
		void GameResume()
		{
			if (GameManager::GetInstance()->GetStat() == GameStat::paused)
			{
				GameManager::GetInstance()->OnResume();
				//回退到游戏界面
				UiManager::GetInstance()->Back();
				//隐藏背景
				Background::GetInstance()->Hide();
			}
		}

		//游戏退出
		void GameExit()
		{
			//游戏结束
			GameManager::GetInstance()->OnExit();
			//退回游戏界面
			UiManager::GetInstance()->Back();
			//退回选关界面
			UiManager::GetInstance()->Back();
			//退回主界面
			UiManager::GetInstance()->Back();
			//显示背景
			Background::GetInstance()->Show();
		}

		//游戏结束
		void GameOver(GameRecord record)
		{
			//退回选关界面
			UiManager::GetInstance()->Back();
			//退回主界面
			UiManager::GetInstance()->Back();
			//设置结束界面数据
			ggLevelNameText->SetStr(record.levelName);
			ggScoreText->SetStr(std::to_string(record.score));
			//添加记录
			Standing::GetInstance()->AddRecord(record);
			//保存记录
			Standing::GetInstance()->Save();
			//跳到结束界面
			UiManager::GetInstance()->Enter(&gameOverLayout);
			//显示背景
			Background::GetInstance()->Show();
		}

		//跳转到选关界面
		void EnterSelectLevel()
		{
			UiManager::GetInstance()->Enter(&selectLevelLayout);
			//加载关卡列表
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

		//跳转到关于界面
		void EnterAbouts()
		{
			UiManager::GetInstance()->Enter(&aboutsLayout);
		}

		//跳转到排名界面
		void EnterStanding()
		{
			UiManager::GetInstance()->Enter(&standingLayout);
			//加载排名
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

		//游戏开始
		void StartGame()
		{	
			if (levelPaths.size())
			{
				if (GameManager::GetInstance()->OnStart(levelPaths[levelList->GetCurrentIndex()], false))
				{
					//隐藏背景
					Background::GetInstance()->Hide();
					UiManager::GetInstance()->Enter(&gameLayout);
				}
			}
		}

		//快速模式游戏开启
		void StartGameFastMode()
		{
			if (levelPaths.size())
			{
				if (GameManager::GetInstance()->OnStart(levelPaths[levelList->GetCurrentIndex()], true))
				{
					//隐藏背景
					Background::GetInstance()->Hide();
					UiManager::GetInstance()->Enter(&gameLayout);
				}
			}
		}

		//程序结束
		void Exit()
		{
			Application::GetInstance()->Exit();
		}

		//跳转到设置界面
		void EnterSettings()
		{
			UiManager::GetInstance()->Enter(&settingsLayout);
		}

		//保存设置
		void SaveSettings()
		{
			Settings::GetInstance()->Save();
			UiManager::GetInstance()->Back();
		}

		//取消设置
		void CancelSettings()
		{
			Settings::GetInstance()->Load();
			UiManager::GetInstance()->Back();
		}
	}



	void Init()
	{
		//-------------------------------------主菜单------------------------------------//

		{
			//开始游戏按钮
			Button* startBtn = new Button("START", Qt::Key::Key_Return);
			startBtn->x = Def::trackWidth / 2, startBtn->y = Def::trackHeight / 2;
			startBtn->w = 200, startBtn->h = 40;
			startBtn->anchor = Anchor::Center;
			QObject::connect(startBtn, &Button::ClickSignal, &Action::EnterSelectLevel);

			//记录按钮
			Button* recordBtn = new Button("RECORD");
			recordBtn->x = Def::trackWidth / 2, recordBtn->y = Def::trackHeight / 2 - 50;
			recordBtn->w = 180, recordBtn->h = 35;
			recordBtn->anchor = Anchor::Center;
			QObject::connect(recordBtn, &Button::ClickSignal, &Action::EnterStanding);

			//设置按钮
			Button* settingsBtn = new Button("SETTINGS");
			settingsBtn->x = Def::trackWidth / 2, settingsBtn->y = Def::trackHeight / 2 - 90;
			settingsBtn->w = 180, settingsBtn->h = 35;
			settingsBtn->anchor = Anchor::Center;
			QObject::connect(settingsBtn, &Button::ClickSignal, &Action::EnterSettings);

			//关于按钮
			Button* aboutBtn = new Button("ABOUT");
			aboutBtn->x = Def::trackWidth / 2, aboutBtn->y = Def::trackHeight / 2 - 130;
			aboutBtn->w = 180, aboutBtn->h = 35;
			aboutBtn->anchor = Anchor::Center;
			QObject::connect(aboutBtn, &Button::ClickSignal, &Action::EnterAbouts);

			//结束按钮
			Button* exitBtn = new Button("EXIT", Qt::Key::Key_Escape);
			exitBtn->x = Def::trackWidth / 2, exitBtn->y = Def::trackHeight / 2 - 180;
			exitBtn->w = 180, exitBtn->h = 35;
			exitBtn->anchor = Anchor::Center;
			QObject::connect(exitBtn, &Button::ClickSignal, &Action::Exit);

			//标题
			Image* title = new Image(Def::resPath + "tex/title.png");
			title->x = Def::trackWidth * 0.5, title->y = Def::trackHeight * 0.7;
			title->w = Def::trackWidth * 0.7, title->h = 100;
			title->anchor = Anchor::Center;

			//版本号
			Text* version = new Text("V 0.0.4", 20);
			version->x = 10.0, version->y = 10.0;
			version->anchor = Anchor::LeftBottom;

			mainMenuLayout.AddWidget(startBtn);
			mainMenuLayout.AddWidget(exitBtn);
			mainMenuLayout.AddWidget(settingsBtn);
			mainMenuLayout.AddWidget(recordBtn);
			mainMenuLayout.AddWidget(aboutBtn);
			mainMenuLayout.AddWidget(title);
			mainMenuLayout.AddWidget(version);
		}

		//-----------------------------------选关界面-----------------------------------//

		{
			//标题
			Text* text = new Text("SELECT DICTIONARY", 40, Qt::green);
			text->x = Def::trackWidth / 2, text->y = Def::trackHeight * 0.8;
			text->anchor = Anchor::Center;

			//向上按钮
			Button* upBtn = new Button("UP", Qt::Key::Key_Up);
			upBtn->x = Def::trackWidth * 0.75, upBtn->y = Def::trackHeight / 2 - 60 + 120;
			upBtn->w = 100, upBtn->h = 35;
			upBtn->anchor = Anchor::Center;

			//向下按钮
			Button* downBtn = new Button("DOWN", Qt::Key::Key_Down);
			downBtn->x = Def::trackWidth * 0.75, downBtn->y = Def::trackHeight / 2 - 60 - 120;
			downBtn->w = 100, downBtn->h = 35;
			downBtn->anchor = Anchor::Center;

			//选关列表
			levelList = new RecordList(5);
			levelList->x = Def::trackWidth * 0.75, levelList->y = Def::trackHeight / 2 - 60;
			levelList->w = Def::trackWidth * 0.5, levelList->h = Def::trackHeight * 0.3;
			levelList->BindDownButton(downBtn);
			levelList->BindUpButton(upBtn);
			levelList->anchor = Anchor::Center;

			//返回按钮
			Button* backBtn = new Button("BACK", Qt::Key::Key_Escape);
			backBtn->x = 10, backBtn->y = 10;
			backBtn->w = 100, backBtn->h = 30;
			backBtn->anchor = Anchor::LeftBottom;
			QObject::connect(backBtn, &Button::ClickSignal, &Action::Back);

			//开始游戏按钮
			Button* startBtn = new Button("START", Qt::Key::Key_Return);
			startBtn->x = 110, startBtn->y = Def::trackHeight / 2 - 40;
			startBtn->w = 140, startBtn->h = 40;
			startBtn->anchor = Anchor::Center;
			QObject::connect(startBtn, &Button::ClickSignal, &Action::StartGame);

			//开始快速游戏按钮
			Button* fastStartBtn = new Button("FAST GAME");
			fastStartBtn->x = 110, fastStartBtn->y = Def::trackHeight / 2 - 100;
			fastStartBtn->w = 140, fastStartBtn->h = 27;
			fastStartBtn->anchor = Anchor::Center;
			QObject::connect(fastStartBtn, &Button::ClickSignal, &Action::StartGameFastMode);

			selectLevelLayout.AddWidget(text);
			selectLevelLayout.AddWidget(levelList);
			selectLevelLayout.AddWidget(downBtn);
			selectLevelLayout.AddWidget(backBtn);
			selectLevelLayout.AddWidget(upBtn);
			selectLevelLayout.AddWidget(startBtn);
			selectLevelLayout.AddWidget(fastStartBtn);
		}

		//-----------------------------------暂停界面-----------------------------------//

		{
			//暂停字样
			Text* text = new Text("PAUSED", 45, Qt::yellow);
			text->x = Def::trackWidth / 2, text->y = Def::trackHeight / 2 + 50;
			text->anchor = Anchor::Center;

			//恢复按钮
			Button* resumeBtn = new Button("RESUME", Qt::Key::Key_Escape);
			resumeBtn->x = Def::trackWidth / 2, resumeBtn->y = Def::trackHeight / 2 - 40;
			resumeBtn->w = 160, resumeBtn->h = 35;
			resumeBtn->anchor = Anchor::Center;
			QObject::connect(resumeBtn, &Button::ClickSignal, &Action::GameResume);

			//退出按钮
			Button* exitBtn = new Button("EXIT");
			exitBtn->x = Def::trackWidth / 2, exitBtn->y = Def::trackHeight / 2 - 100;
			exitBtn->w = 160, exitBtn->h = 35;
			exitBtn->anchor = Anchor::Center;
			QObject::connect(exitBtn, &Button::ClickSignal, &Action::GameExit);

			pauseLayout.AddWidget(text);
			pauseLayout.AddWidget(resumeBtn);
			pauseLayout.AddWidget(exitBtn);
		}

		//-----------------------------------游戏界面-----------------------------------//

		{
			//暂停按钮（隐藏）
			Button* pauseBtn = new Button("PAUSE", Qt::Key::Key_Escape);
			pauseBtn->visible = false;
			QObject::connect(pauseBtn, &Button::ClickSignal, &Action::GamePause);

			gameLayout.AddWidget(pauseBtn);
		}

		//---------------------------------游戏结束界面---------------------------------//

		{
			//游戏结束字样
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

			//返回按钮
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

		//-------------------------------------关于界面----------------------------------//

		{
			//返回按钮
			Button* backBtn = new Button("BACK", Qt::Key::Key_Escape);
			backBtn->x = 10, backBtn->y = 10;
			backBtn->w = 100, backBtn->h = 30;
			backBtn->anchor = Anchor::LeftBottom;
			QObject::connect(backBtn, &Button::ClickSignal, &Action::Back);

			//abouts信息
			Image* about = new Image(Def::resPath + "tex/abouts.png");
			about->w = Def::trackWidth, about->h = Def::trackHeight * 0.9;
			about->anchor = Anchor::LeftBottom;

			aboutsLayout.AddWidget(backBtn);
			aboutsLayout.AddWidget(about);
		}

		//-------------------------------------排名界面----------------------------------//

		{
			//返回按钮
			Button* backBtn = new Button("BACK", Qt::Key::Key_Escape);
			backBtn->x = 10, backBtn->y = 10;
			backBtn->w = 100, backBtn->h = 30;
			backBtn->anchor = Anchor::LeftBottom;
			QObject::connect(backBtn, &Button::ClickSignal, &Action::Back);

			//向上按钮
			Button* upBtn = new Button("UP", Qt::Key::Key_Up);
			upBtn->x = 200, upBtn->y = 10;
			upBtn->w = 100, upBtn->h = 35;
			backBtn->anchor = Anchor::LeftBottom;

			//向下按钮
			Button* downBtn = new Button("DOWN", Qt::Key::Key_Down);
			downBtn->x = 350, downBtn->y = 10;
			downBtn->w = 100, downBtn->h = 35;
			backBtn->anchor = Anchor::LeftBottom;

			//排名信息
			standingRankList = new RecordList(15);
			standingRankList->x = 5, standingRankList->y = 70;
			standingRankList->w = Def::trackWidth * 0.9, standingRankList->h = Def::trackHeight * 0.6;
			standingRankList->anchor = Anchor::LeftBottom;
			standingRankList->BindDownButton(downBtn);
			standingRankList->BindUpButton(upBtn);

			//分数信息
			standingScoreList = new RecordList(15);
			standingScoreList->x = 50, standingScoreList->y = 70;
			standingScoreList->w = Def::trackWidth * 0.9, standingScoreList->h = Def::trackHeight * 0.6;
			standingScoreList->anchor = Anchor::LeftBottom;
			standingScoreList->BindDownButton(downBtn);
			standingScoreList->BindUpButton(upBtn);

			//关卡名信息
			standingLevelNameList = new RecordList(15);
			standingLevelNameList->x = 150, standingLevelNameList->y = 70;
			standingLevelNameList->w = Def::trackWidth * 0.9, standingLevelNameList->h = Def::trackHeight * 0.6;
			standingLevelNameList->anchor = Anchor::LeftBottom;
			standingLevelNameList->BindDownButton(downBtn);
			standingLevelNameList->BindUpButton(upBtn);

			//时间信息
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

		//-----------------------------------设置界面-----------------------------------//

		{
			//标题
			Text* text = new Text("SETTINGS", 40, Qt::green);
			text->x = Def::trackWidth / 2, text->y = Def::trackHeight * 0.8;
			text->anchor = Anchor::Center;

			//取消按钮
			Button* cancelBtn = new Button("CANCEL", Qt::Key::Key_Escape);
			cancelBtn->x = Def::trackWidth * 0.25, cancelBtn->y = 30;
			cancelBtn->w = 140, cancelBtn->h = 30;
			cancelBtn->anchor = Anchor::Center;
			QObject::connect(cancelBtn, &Button::ClickSignal, &Action::CancelSettings);

			//保存按钮
			Button* saveBtn = new Button("SAVE", Qt::Key::Key_Return);
			saveBtn->x = Def::trackWidth * 0.75, saveBtn->y = 30;
			saveBtn->w = 140, saveBtn->h = 30;
			saveBtn->anchor = Anchor::Center;
			QObject::connect(saveBtn, &Button::ClickSignal, &Action::SaveSettings);

			//设置:bgm音量
			Text* bgmText = new Text("BGM VOLUME", 23);
			bgmText->x = 50, bgmText->y = 300;
			bgmText->anchor = Anchor::LeftBottom;
			SlideBar* bgmBar = new SlideBar(&Settings::GetInstance()->bgmVol, 0.0, 1.0);
			bgmBar->x = Def::trackWidth * 0.6, bgmBar->y = 300 - 5;
			bgmBar->w = 150, bgmBar->h = 25;
			bgmBar->anchor = Anchor::LeftBottom;

			//设置:se音量
			Text* seText = new Text("SE VOLUME", 23);
			seText->x = 50, seText->y = 270;
			seText->anchor = Anchor::LeftBottom;
			SlideBar* seBar = new SlideBar(&Settings::GetInstance()->seVol, 0.0, 1.0);
			seBar->x = Def::trackWidth * 0.6, seBar->y = 270 - 5;
			seBar->w = 150, seBar->h = 25;
			seBar->anchor = Anchor::LeftBottom;

			//设置：粒子效果
			Text* particleText = new Text("HIGH QUALITY", 23);
			particleText->x = 50, particleText->y = 230;
			particleText->anchor = Anchor::LeftBottom;
			Switcher* particleSwc = new Switcher(&Settings::GetInstance()->showParticle);
			particleSwc->x = Def::trackWidth * 0.6, particleSwc->y = 230 - 5;
			particleSwc->w = 150, particleSwc->h = 25;
			particleSwc->anchor = Anchor::LeftBottom;

			//设置：记录
			Text* recordText = new Text("GAME RECORDING", 23);
			recordText->x = 50, recordText->y = 200;
			recordText->anchor = Anchor::LeftBottom;
			Switcher* recordSwc = new Switcher(&Settings::GetInstance()->record);
			recordSwc->x = Def::trackWidth * 0.6, recordSwc->y = 200 - 5;
			recordSwc->w = 150, recordSwc->h = 25;
			recordSwc->anchor = Anchor::LeftBottom;

			//设置:note缩放
			Text* noteScaleText = new Text("NOTE SCALE", 23);
			noteScaleText->x = 50, noteScaleText->y = 170;
			noteScaleText->anchor = Anchor::LeftBottom;
			SlideBar* noteScaleBar = new SlideBar(&Settings::GetInstance()->noteScale, 0.5, 1.5);
			noteScaleBar->x = Def::trackWidth * 0.6, noteScaleBar->y = 170 - 5;
			noteScaleBar->w = 150, noteScaleBar->h = 25;
			noteScaleBar->anchor = Anchor::LeftBottom;

			settingsLayout.AddWidget(text);
			settingsLayout.AddWidget(cancelBtn);
			settingsLayout.AddWidget(saveBtn);
			settingsLayout.AddWidget(particleSwc);
			settingsLayout.AddWidget(particleText);
			settingsLayout.AddWidget(recordSwc);
			settingsLayout.AddWidget(recordText);
			settingsLayout.AddWidget(noteScaleText);
			settingsLayout.AddWidget(noteScaleBar);
			settingsLayout.AddWidget(bgmText);
			settingsLayout.AddWidget(bgmBar);
			settingsLayout.AddWidget(seText);
			settingsLayout.AddWidget(seBar);
		}

		//-----------------------------------------------------------------------------//

		//添加到ui管理器的绘图列表
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
