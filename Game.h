#pragma once

#include <qwidget.h>

#include <list>
#include <map>
#include <string>
#include <vector>

class Note;
class ParticleManager;

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

class Game : public QWidget
{
	Q_OBJECT

public:

	Game(QWidget* parent = nullptr);

	~Game();


	void Start(const std::string& name);

	void Pause();

	void Continue();

protected:

	void timerEvent(QTimerEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

	void keyPressEvent(QKeyEvent* event) override;

	void keyReleaseEvent(QKeyEvent* event) override;

private:

	QTime* clock;

	ParticleManager* particleMgr;

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

	void ResetAll();

	bool LoadLevel(const std::string& name);

	void InitNotes();

	void Update();

signals:

};
