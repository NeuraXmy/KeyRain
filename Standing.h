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
class Standing : public QObject
{
	Q_OBJECT

public:
	
	static Standing* GetInstance();

	static void ReleaseInstance();


	void AddRecord(GameRecord record);

	void SaveRecord();

	void LoadRecord();


	std::vector<GameRecord> GetRecord() const;
	

private:

	Standing();

	~Standing();

	std::priority_queue<GameRecord> records;

};