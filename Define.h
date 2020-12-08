//Define.h: ���������ͺ���������

#pragma once

#include <string>

class QColor;

struct Particle;


//���������뺯�������ռ�
namespace Def
{
	extern const double pi;

	//---------------------�������------------------------//

	extern const int tickTime;
	extern const double tickCount;

	extern const int frameTime;

	extern const int inputTickTime;

	extern const int uiTick;
	
	extern const std::string resPath;

	extern const std::string profilePath;

	//---------------------�Ӿ����------------------------//
	
	extern const int windowWidth;
	extern const int windowHeight;

	extern const int keySize;
	extern const int keySpace;
	extern const int keyboardPosX;
	extern const int keyboardPosY;
	extern const int keyIndexX[];
	extern const int keyIndexY[];
	
	extern const int scorePosX;
	extern const int scorePosY;

	extern const int trackWidth;
	extern const int trackHeight;
	extern const int trackPosX;
	extern const int trackPosY;

	extern const double maxTrackShake;
	extern const double trackShakeDecreseSpeed;

	extern const int noteSize;
	extern const int noteTrackWidth;

	extern const std::string bonusTitle[];
	extern const QColor bonusColor[];

	extern const QColor btnColor;
	extern const QColor btnHoverColor;
	extern const QColor btnDownColor;
	extern const QColor btnDisabledColor;

	extern const QColor recordListColor;
	extern const QColor recordListHighlightColor;

	extern const int bgCharNum;
	extern const double bgCharSpeed;

	//---------------------��Ϸ�������--------------------//

	extern const int gameStandbyTime;

	extern const int noteBasicScore;
	extern const int comboBonusScore;
	extern const int noteLostScore;
	extern const int noteMissScore;

	extern const int maxHealth;
	extern const int comboHealth;
	extern const int noteLostHealth;
	extern const int noteMissHealth;

	extern const double maxFever;
	extern const double feverIncreaseSpeed;
	extern const int feverStandByTime;
	extern const double feverProcessSpeedUp;

	extern const double diffIncreaseSpeed;
	extern const double noteSpeedStart;
	extern const double noteSpeedEnd;
	extern const double noteSlowDownStart;
	extern const double noteSlowDownEnd;
	extern const double noteIntervalStart;
	extern const double noteIntervalEnd;
	extern const double noteProcessFeverEffect;

	extern const int bonusCombo;
	extern const int bonusTime[];
	extern const int bonusScore;

	//---------------------����Ч�����--------------------//

	extern const int particleFlashInterval;

	extern const int noteClearParticleNum;
	extern const Particle noteClearParticle;

	extern const int noteLostParticleNum;
	extern const Particle noteLostParticle;

	extern const int noteDragParticleInterval;
	extern const Particle noteDragParticle;

	extern const int feverParticleInterval;;
	extern const Particle feverParticle;

	//---------------------���ߺ���------------------------//

	//��ȡ[l,r]�ڵ��������
	int RandInt(int l, int r);
	
	//��ȡ[l,r]�ڵ����������
	double RandReal(double l, double r);

	//�������������
	void SetRandSeed(unsigned long long seed);
}
