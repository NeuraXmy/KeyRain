//SoundManager.h: 音效管理器类型

#pragma once

#include <string>
#include <list>

#include <qsoundeffect.h>
#include <qthread.h>



/**
* SoundEffect (QObject)
* 封装的音效类型
* 便于qsoundeffect的信号连接
*/
class SoundEffect final : public QObject
{
	Q_OBJECT

public:

	SoundEffect(QThread* thread, const std::string& name, bool repeat = false);

	~SoundEffect();

	void SetVol(double vol);

	void Play();

	void Stop();

signals:

	void PlaySignal();

	void StopSignal();

	void SetVolSignal(qreal vol);

private:

	QSoundEffect* sound;

};



/**
* SoundManager
* 控制音效播放的单例类型
*/
class SoundManager final
{
public:

	static SoundManager* GetInstance();

	static void ReleaseInstance();



	void PlaySe(SoundEffect* se) const;

	void PlayBgm(SoundEffect* bgm) const;

	void StopSe(SoundEffect* se) const;

	void StopBgm(SoundEffect* bgm) const;

private:

	SoundManager();

	~SoundManager();

	QThread* thread;

	std::list<SoundEffect*> soundList;

};



namespace Se
{
	extern SoundEffect* noteHit;
	extern SoundEffect* noteLost;
	extern SoundEffect* explode;
	extern SoundEffect* buttonClick;
}

namespace Bgm
{

}