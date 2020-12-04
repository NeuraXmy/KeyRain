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
	int bgmVol;
	//��Ϸ��Ч����
	int seVol;
	//�Ƿ���ʾ����
	bool showParticle;
	//note����
	double noteScale;


	void Save() const;

	void Load();

private:

	Settings();

	~Settings();

};