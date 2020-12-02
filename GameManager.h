//GameManger.h�� ��Ϸ����������

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


//��Ϸ��״̬
enum GameStat
{
	running,
	preparing,
	paused,
	ended
};

//fever��״̬
enum FeverMode
{
	notFever,
	standby,
	fever
};



/**
* GameManager (QWidget)
* ������Ϸ���̵Ŀ�������������
*/
class GameManager : public QWidget
{
	Q_OBJECT

public:

	static GameManager* GetInstance();

	static void ReleaseInstance();

	
	//���ƹ��
	void DrawTrack(QPainter* painter) const;

	//������Ϸ����
	void DrawGui(QPainter* painter) const;


	//��ȡ��Ϸ״̬
	int GetStat() const;



	//��ʼ�ʿ�Ϊname��һ����Ϸ
	void OnStart(const std::string& name);

	//��Ϸ��ͣ
	void OnPause();

	//��Ϸ����
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

	//��Ϸʱ��
	int time;

	std::string levelName;

	std::vector<std::string> words;
	
	std::list<Note*> notes;

	//������İ�������
	std::list<int> keys;

	//ĳ�����Ƿ���
	mutable std::map<int, bool> keyHolding;

	int stat;

	//------------------------------------�������-------------------------------------//

	int combo;
	//��ȡ��һ����������Ҫ��������
	int nextBonusCombo;

	int score;
	//ʵ����ʾ�ķ���
	int scoreDisplaying;

	int bonusMode;
	int bonusStartTime = 0;

	int health;

	double fever;
	int feverStartTime;
	int feverMode;

	//�Ѿ������İ�������
	int noteCount;

	double noteSpeed;
	double noteSlowDown;
	double noteInterval;

	//------------------------------------�Ӿ����-------------------------------------//

	//���̰���������ɫ
	mutable std::map<int, QColor> keyColor;
	//����ײ�������ɫ
	QColor bottomLightColor;
	//����ײ����⽥��߶�
	double bottomLightHeight;

	QColor healthBarColor;
	QColor feverBarColor;
	QColor comboBarColor;
	QColor scoreBarColor;

	//���ƹ���𶯱���
	double trackShake;



	GameManager();

	~GameManager();



	//������Ϸ
	void ResetAll();

	//������Ϊname�Ĵʿ⣬�����Ƿ�ɹ�
	bool LoadLevel(const std::string& name);

	//��words�м���notes
	void InitNotes();

	//����һ��Ϸ֡����
	void Update();

};
