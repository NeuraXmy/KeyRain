//Define.cpp: 公共变量和函数的定义

#include "Define.h"
#include "Particle.h"

#include <random>
#include <qcolor.h>

namespace Def
{
	const double pi = acos(-1.0);

	//---------------------程序相关------------------------//

	const int tickTime = 10;
	const double tickCount = 1000.0 / tickTime;

	const int frameTime = 10;

	const int inputTickTime = 10;

	const int uiTick = 20;

	const std::string resPath = "../resources/";

	const std::string profilePath = "../profiles/";

	//---------------------视觉相关------------------------//

	const int keySize = 45;
	const int keySpace = 7;
	const int keyboardPosX = 40;
	const int keyboardPosY = 25;
	const int keyIndexX[] =
	{
		1, 5, 3, 3, 3, 4, 5, 
		6, 8, 7, 8, 9, 7, 6, 
		9, 10, 1, 4, 2, 5, 7, 
		4, 2, 2, 6, 1
	};
	const int keyIndexY[] =
	{
		2, 1, 1, 2, 3, 2, 2, 
		2, 3, 2, 2, 2, 1, 1, 
		3, 3, 3, 3, 2, 3, 3,
		1, 3, 1, 3, 1
	};

	const int windowWidth = 600;
	const int windowHeight = 700;

	const int trackWidth = 550;
	const int trackHeight = 450;
	const int trackPosX = 25;
	const int trackPosY = 275;

	const double maxTrackShake = 5.0;
	const double trackShakeDecreseSpeed = 0.15;

	const int noteSize = 45;
	const int noteTrackWidth = 45;

	const int scorePosX = 35;
	const int scorePosY = 200;

	const std::string bonusTitle[] =
	{
		"",
		"SPEED UP",
		"SLOW DOWN",
		"REVERSE",
		"RANDOM"
	};
	const QColor bonusColor[] =
	{
		QColor(0, 0, 0),
		QColor(10, 50, 255),
		QColor(255, 50, 10),
		QColor(50, 255, 255),
		QColor(255, 50, 200)
	};

	const QColor btnColor = Qt::green;
	const QColor btnHoverColor = Qt::yellow;
	const QColor btnDownColor = Qt::white;
	const QColor btnDisabledColor = QColor(20, 100, 20);

	const QColor recordListColor = Qt::green;
	const QColor recordListHighlightColor = Qt::yellow;

	//---------------------游戏内容相关--------------------//

	const int gameStandbyTime = 3000;

	const int noteBasicScore = 20;
	const int comboBonusScore = 1;
	const int noteLostScore = -10;
	const int noteMissScore = -5;

	const int maxHealth = 1000;
	const int comboHealth = 1;
	const int noteLostHealth = -100;
	const int noteMissHealth = -50;

	const double maxFever = 1000;
	const double feverIncreaseSpeed = 35;
	const int feverStandByTime = 3000;
	const int feverTime = 8000;
	const double feverProcessSpeedUp = 5;

	const double diffIncreaseSpeed = 0.0012;
	const double noteSpeedStart = 300.0;
	const double noteSpeedEnd = 1000.0;
	const double noteSlowDownStart = 0.95;
	const double noteSlowDownEnd = 0.999;
	const double noteIntervalStart = 0.4;
	const double noteIntervalEnd = 0.15;
	const double noteProcessFeverEffect = 10.0;

	const int bonusCombo = 20;
	const int bonusTime[] =
	{
		0, 10000, 10000, 10000, 10000
	};

	const int bonusScore = 100;

	//---------------------粒子效果相关--------------------//

	const int particleFlashInterval = 20;

	const int noteClearParticleNum = 3;
	const Particle noteClearParticle = Particle(500, 0.01, 7);

	const int noteLostParticleNum = 4;
	const Particle noteLostParticle = Particle(500, 0.01, 7, Qt::red);

	const int noteDragParticleInterval = 300;
	const Particle noteDragParticle = Particle(500, 0.005, 5);

	const int feverParticleInterval = 300;
	const Particle feverParticle = Particle(3000, 0.005, 5);

	//---------------------工具函数------------------------//

	//随机数引擎
	std::default_random_engine re;

	int RandInt(int l, int r)
	{
		std::uniform_int_distribution<int> u(l, r);
		return u(re);
	}

	double RandReal(double l, double r)
	{
		std::uniform_real_distribution<double> u(l, r);
		return u(re);
	}

	void SetRandSeed(unsigned long long seed)
	{
		re.seed(seed);
	}
}

