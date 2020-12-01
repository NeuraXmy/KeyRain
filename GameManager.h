#pragma once

#include <qwidget.h>

#include <list>
#include <map>
#include <string>
#include <vector>

class Note;
class ParticleManager;
class UiManager;

class QTime;
class QImage;

enum GameStat
{
	running,
	preparing,
	paused,
	ended
};

enum FeverMode
{
	notFever,
	standby,
	fever
};

class GameManager : public QWidget
{
	Q_OBJECT

public:

	static GameManager* GetInstance();

	static void ReleaseInstance();

	void Start(const std::string& name);

	int GetStat() const;
	
	void OnPause();

	void OnResume();

	void OnKeyPressEvent(int key);

	void OnKeyReleaseEvent(int key);

protected:

	void timerEvent(QTimerEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

private:

	QTime* clock;

	int timerId;

	int time;

	int combo;
	int nextBonusCombo;

	int score;
	int scoreDisplaying;

	std::string levelName;

	std::list<Note*> notes;

	std::vector<std::string> words;

	std::list<int> keys;

	std::map<int, bool> keyHolding;

	int stat;

	int noteCount;

	int bonusMode;
	int bonusStartTime = 0;

	int health;

	double fever;
	int feverStartTime;
	int feverMode;

	mutable std::map<int, QColor> keyColor;
	mutable QColor bottomLightColor;
	mutable double bottomLightHeight;
	mutable QColor healthBarColor;
	mutable QColor feverBarColor;
	mutable QColor comboBarColor;
	mutable QColor scoreBarColor;

	mutable double trackShake;

	QImage* interfaceImage;
	QImage* keyImage;
	QImage* keyDownImage;

	double noteSpeed;
	double noteSlowDown;
	double noteInterval;

	GameManager();

	~GameManager();

	void ResetAll();

	bool LoadLevel(const std::string& name);

	void InitNotes();

	void Update();

signals:

};
