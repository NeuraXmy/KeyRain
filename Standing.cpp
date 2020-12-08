//Standing.cpp: 游戏排名类型

#include "Standing.h"
#include "Define.h"
#include "GameManager.h"
#include "Settings.h"

#include <fstream>
#include <iomanip>

#include <qdebug.h>



namespace
{
	Standing* instance = nullptr;
}

Standing* Standing::GetInstance()
{
	if (!instance)
	{
		instance = new Standing();
	}
	return instance;
}

void Standing::ReleaseInstance()
{
	if (instance)
	{
		delete instance;
	}
}



Standing::Standing()
	: QObject()
{

}

Standing::~Standing()
{

}



void Standing::AddRecord(GameRecord record)
{
	if (Settings::GetInstance()->record)
	{
		records.push(record);
	}
}

void Standing::Save()
{
	std::string path = Def::profilePath + "records.dat";
	std::ofstream out(path);

	auto recs = records;

	if (!out)
	{
		qDebug() << "[ERR] Failed to save records";
		return;
	}

	out << recs.size() << std::endl;
	while(recs.size())
	{
		GameRecord rec = recs.top();
		recs.pop();

		out << rec.score << std::endl;
		out << rec.levelName << std::endl;
		out << rec.time << std::endl;
	}

	out.close();

	qDebug() << "[INF] Records saved";
}

void Standing::Load()
{
	while (records.size())
	{
		records.pop();
	}

	std::string path = Def::profilePath + "records.dat";
	std::ifstream in(path);

	if (!in)
	{
		qDebug() << "[INF] No record";
		return;
	}

	int recordCount = 0;
	in >> recordCount;
	for (int i = 0; i < recordCount; i++)
	{
		GameRecord rec;
		in >> rec.score;
		in.get();
		std::getline(in, rec.levelName);
		std::getline(in, rec.time);

		records.push(rec);
	}

	in.close();

	qDebug() << "[INF] Records loaded";
}

std::vector<GameRecord> Standing::GetRecord() const
{
	auto recs = records;
	std::vector<GameRecord> ret;

	int rank = 0;
	while (recs.size())
	{
		GameRecord rec = recs.top();
		rec.rank = ++rank;
		recs.pop();
		ret.push_back(rec);
	}
	return ret;
}

