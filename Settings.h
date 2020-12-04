//Setting.h: 游戏设置

#pragma once



/**
* Settings
* 掌管游戏设置相关变量的单例类型
*/
class Settings final
{
public:

	static Settings* GetInstance();

	static void ReleaseInstance();

	//背景音乐音量
	int bgmVol;
	//游戏音效音量
	int seVol;
	//是否显示粒子
	bool showParticle;
	//note缩放
	double noteScale;


	void Save() const;

	void Load();

private:

	Settings();

	~Settings();

};