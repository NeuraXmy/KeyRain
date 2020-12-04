//Standing.h: 游戏排名类型

#pragma once

#include "GameManager.h"

#include <qobject.h>

#include <vector>
#include <queue>
#include <string>



/**
* Standing (QObject)
* 存储游戏中的排名的单例类
*/
class Standing final : public QObject
{
	Q_OBJECT

public:
	
	static Standing* GetInstance();

	static void ReleaseInstance();


	void AddRecord(GameRecord record);

	void Save();

	void Load();


	std::vector<GameRecord> GetRecord() const;
	

private:

	Standing();

	~Standing();

	std::priority_queue<GameRecord> records;

};