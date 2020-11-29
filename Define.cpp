#include "Define.h"
#include "Particle.h"

#include <random>

namespace Def
{
	const double pi = acos(-1.0);

	const int tickTime = 10;
	const double tickCount = 1000.0 / tickTime;
	const int frameTime = 10;
	const double frameCount = 1000.0 / frameTime;

	const std::string resPath = "./res/";

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

	const int noteBasicScore = 20;
	const int comboBonusScore = 1;
	const int noteLostScore = -10;
	const int noteMissScore = -5;

	const int maxHealth = 1000;
	const int comboHealth = 1;
	const int noteLostHealth = -20;
	const int noteMissHealth = -10;

	const double maxFever = 1000;
	const double feverIncreaseSpeed = 30;
	const int feverStandByTime = 3000;
	const int feverTime = 8000;
	const double feverProcessSpeedUp = 5;

	const double diffIncreaseSpeed = 0.001;
	const double noteSpeedStart = 300.0;
	const double noteSpeedEnd = 1000.0;
	const double noteSlowDownStart = 0.95;
	const double noteSlowDownEnd = 0.999;
	const double noteIntervalStart = 0.4;
	const double noteIntervalEnd = 0.15;
	const double noteProcessFeverEffect = 10.0;

	const int noteClearParticleNum = 3;
	const Particle noteClearParticle = Particle(500, 0.01, 7);
	const int noteLostParticleNum = 4;
	const Particle noteLostParticle = Particle(500, 0.01, 7, Qt::red);
	const int noteDragParticleInterval = 300;
	const Particle noteDragParticle = Particle(500, 0.005, 5);
	const int feverParticleInterval = 300;
	const Particle feverParticle = Particle(3000, 0.005, 5);

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
