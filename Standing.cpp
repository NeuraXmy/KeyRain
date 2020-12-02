//Standing.cpp: 游戏排名类型

#include "Standing.h"
#include "Define.h"
#include "GameManager.h"

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
	delete instance;
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
	records.push(record);
}

void Standing::SaveRecord()
{
	std::string path = Def::profilePath + "records.rec";
	std::ofstream out(path);

	if (!out)
	{
		qDebug() << "[ERR] Failed to save records";
		return;
	}

	out << records.size() << std::endl;
	while(records.size())
	{
		GameRecord rec = records.top();
		records.pop();

		out << rec.score << std::endl;
		out << rec.levelName << std::endl;
		out << rec.time << std::endl;
	}

	out.close();
}

void Standing::LoadRecord()
{
	while (records.size())
	{
		records.pop();
	}

	std::string path = Def::profilePath + "records.rec";
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

