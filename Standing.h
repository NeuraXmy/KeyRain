//Standing.h: ��Ϸ��������

#pragma once

#include "GameManager.h"

#include <qobject.h>

#include <vector>
#include <queue>
#include <string>



/**
* Standing (QObject)
* �洢��Ϸ�е������ĵ�����
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