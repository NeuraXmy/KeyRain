//GameManger.h： 游戏管理器类型

#pragma once

#include <qwidget.h>

#include <list>
#include <map>
#include <string>
#include <vector>

class QTime;
class QImage;
class QPainter;

class Note;


//游戏的状态
enum GameStat
{
	running,
	preparing,
	paused,
	ended
};

//fever的状态
enum FeverMode
{
	notFever,
	standby,
	fever
};



/**
* GameManager (QWidget)
* 控制游戏进程的控制器单例类型
*/
class GameManager : public QWidget
{
	Q_OBJECT

public:

	static GameManager* GetInstance();

	static void ReleaseInstance();

	
	//绘制轨道
	void DrawTrack(QPainter* painter) const;

	//绘制游戏界面
	void DrawGui(QPainter* painter) const;


	//获取游戏状态
	int GetStat() const;



	//开始词库为name的一轮游戏
	void OnStart(const std::string& name);

	//游戏暂停
	void OnPause();

	//游戏继续
	void OnResume();

	void OnKeyPressEvent(int key);

	void OnKeyReleaseEvent(int key);

signals:

	void GameExitSignal();

	void GameOverSignal();

protected:

	void timerEvent(QTimerEvent* event) override;

private:

	QTime* clock;

	QImage* interfaceImage;
	QImage* keyImage;
	QImage* keyDownImage;

	int timerId;

	//游戏时间
	int time;

	std::string levelName;

	std::vector<std::string> words;
	
	std::list<Note*> notes;

	//待处理的按键队列
	std::list<int> keys;

	//某个键是否按下
	mutable std::map<int, bool> keyHolding;

	int stat;

	//------------------------------------内容相关-------------------------------------//

	int combo;
	//获取下一个奖励所需要的连击数
	int nextBonusCombo;

	int score;
	//实际显示的分数
	int scoreDisplaying;

	int bonusMode;
	int bonusStartTime = 0;

	int health;

	double fever;
	int feverStartTime;
	int feverMode;

	//已经经过的按键数量
	int noteCount;

	double noteSpeed;
	double noteSlowDown;
	double noteInterval;

	//------------------------------------视觉相关-------------------------------------//

	//键盘按键发光颜色
	mutable std::map<int, QColor> keyColor;
	//轨道底部闪光颜色
	QColor bottomLightColor;
	//轨道底部闪光渐变高度
	double bottomLightHeight;

	QColor healthBarColor;
	QColor feverBarColor;
	QColor comboBarColor;
	QColor scoreBarColor;

	//控制轨道震动变量
	double trackShake;



	GameManager();

	~GameManager();



	//重置游戏
	void ResetAll();

	//加载名为name的词库，返回是否成功
	bool LoadLevel(const std::string& name);

	//从words中加载notes
	void InitNotes();

	//进行一游戏帧更新
	void Update();

};
