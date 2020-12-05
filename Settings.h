//Setting.h: ��Ϸ����

#pragma once



/**
* Settings
* �ƹ���Ϸ������ر����ĵ�������
*/
class Settings final
{
public:

	static Settings* GetInstance();

	static void ReleaseInstance();

	//������������
	double bgmVol;
	//��Ϸ��Ч����
	double seVol;
	//�Ƿ���ʾ����
	bool showParticle;
	//�Ƿ��¼
	bool record;
	//note����
	double noteScale;


	void Save() const;

	void Load();

private:

	Settings();

	~Settings();

};