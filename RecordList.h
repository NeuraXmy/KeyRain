//RecordList.h: ��¼�б�����

#pragma once

#include "Widget.h"

#include <qcolor.h>

#include <string>
#include <vector>

class Button;



/**
* Text (Widget)
* ����ui�еļ�¼�б�ؼ�����
* �������Լ�¼չʾ��ѡ��
*/
class RecordList final : public  Widget
{
public:

	RecordList(int maxShowRecordNum);



	void Update(int time) override;

	void Reset() override;

	void Draw(QPainter* painter) const override;



	//����һ����¼
	void OnDown();

	//����һ����¼
	void OnUp();



	//��ȡ��ǰ��¼
	std::string GetCurrentRecord() const;

	//��ȡ��ǰ��¼�ǵڼ���
	int GetCurrentIndex() const;

	//��ȡ��ǰ�ܼ�¼����
	int GetRecordNum() const;

	//��ȡĳ�������µļ�¼
	std::string GetRecord(int index) const;

	//��ռ�¼
	void Clear();

	//�����¼
	void AddRecord(const std::string& record);

	//ɾ����¼��������ڣ�
	void DeleteRecord(const std::string& record);

	//ɾ��ĳ�������µļ�¼
	void DeleteRecord(int index);

	//�����ϵİ�ť
	void BindUpButton(Button* upBtn);

	//�����µİ�ť
	void BindDownButton(Button* downBtn);

private:

	//��ǰ�ļ�¼����
	int current;

	//��ʾ�е�ƫ��
	double showingOffset;

	//�����ʾ�ļ�¼��
	int maxShowRecordNum;

	std::vector<std::string> records;

	Button* upBtn;

	Button* downBtn;

	//��ȡ��ʾ�еĿ�ʼ�����ͽ�������
	std::pair<int, int> GetStartEndIndex() const;

};