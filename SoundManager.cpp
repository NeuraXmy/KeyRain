//SoundManager.cpp: 音效管理器类型

#include "SoundManager.h"
#include "Settings.h"
#include "Define.h"



SoundEffect::SoundEffect(QThread* thread, const std::string& name, bool repeat)
{
	sound = new QSoundEffect();
	sound->setSource(QUrl::fromLocalFile((Def::resPath + "audio/" + name + ".wav").c_str()));
	sound->setLoopCount(repeat ? QSoundEffect::Infinite : 1);

	connect(this, &SoundEffect::PlaySignal, sound, &QSoundEffect::play);
	connect(this, &SoundEffect::StopSignal, sound, &QSoundEffect::stop);
	connect(this, &SoundEffect::SetVolSignal, sound, &QSoundEffect::setVolume);

	sound->moveToThread(thread);
}

SoundEffect::~SoundEffect()
{
	
}

void SoundEffect::SetVol(double vol)
{
	emit SetVolSignal(vol);
}

void SoundEffect::Play()
{
	emit PlaySignal();
}

void SoundEffect::Stop()
{
	emit StopSignal();
}


namespace
{
	SoundManager* instance = nullptr;
}

SoundManager* SoundManager::GetInstance()
{
	if (!instance)
	{
		instance = new SoundManager();
	}
	return instance;
}

void SoundManager::ReleaseInstance()
{
	if (instance)
	{
		delete instance;
	}
}

SoundManager::SoundManager()
{
	thread = new QThread();

	soundList.push_back(Se::noteHit  = new SoundEffect(thread, "note_hit"));
	soundList.push_back(Se::noteLost = new SoundEffect(thread, "note_lost"));
	soundList.push_back(Se::buttonClick = new SoundEffect(thread, "button_click"));

	thread->start();
}

SoundManager::~SoundManager()
{
	if (!thread->isFinished())
	{
		thread->terminate();
	}
	delete thread;

	for (auto sound : soundList)
	{
		if (sound)
		{
			delete sound;
		}
	}
}



void SoundManager::PlaySe(SoundEffect* se) const
{
	if (!se)
	{
		return;
	}
	se->SetVol(Settings::GetInstance()->seVol);
	se->Play();
}

void SoundManager::PlayBgm(SoundEffect* bgm) const
{
	if (!bgm)
	{
		return;
	}
	bgm->SetVol(Settings::GetInstance()->bgmVol);
	bgm->Play();
}

void SoundManager::StopSe(SoundEffect* se) const
{
	if (!se)
	{
		return;
	}
	se->Stop();
}

void SoundManager::StopBgm(SoundEffect* bgm) const
{
	if (!bgm)
	{
		return;
	}
	bgm->Stop();
}



namespace Se
{
	SoundEffect* noteHit		= nullptr;
	SoundEffect* noteLost		= nullptr;
	SoundEffect* explode		= nullptr;
	SoundEffect* buttonClick	= nullptr;
}

namespace Bgm
{

}