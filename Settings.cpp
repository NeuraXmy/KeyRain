//Setting.cpp: ��Ϸ����

#include "Settings.h"
#include "Define.h"

#include <fstream>

#include <qdebug.h>



namespace
{
	Settings* instance = nullptr;
}

Settings* Settings::GetInstance()
{
	if (!instance)
	{
		instance = new Settings;
	}
	return instance;
}

void Settings::ReleaseInstance()
{
	if (instance)
	{
		delete instance;
	}
}



Settings::Settings()
	: bgmVol(100)
	, seVol(100)
	, showParticle(true)
	, noteScale(1.0)
{

}

Settings::~Settings()
{

}



void Settings::Save() const
{
	std::string path = Def::profilePath + "settings.dat";
	std::ofstream out(path);

	if (!out)
	{
		qDebug() << "[ERR] Failed to save settings";
		return;
	}

	out << bgmVol << std::endl;
	out << seVol << std::endl;
	out << showParticle << std::endl;
	out << noteScale << std::endl;

	out.close();

	qDebug() << "[INF] Settings saved";
}

void Settings::Load()
{
	std::string path = Def::profilePath + "settings.dat";
	std::ifstream in(path);

	if (!in)
	{
		qDebug() << "[INF] Cant open settings file, use default settings";
		return;
	}

	in >> bgmVol;
	in >> seVol;
	in >> showParticle;
	in >> noteScale;

	in.close();

	qDebug() << "[INF] Settings loaded";
}


