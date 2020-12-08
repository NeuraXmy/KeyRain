//Background.h: ui界面的背景

#pragma once

#include <list>

class QPainter;



/**
* Background
* ui界面背景的单例类型
*/
class Background
{
public:

	static Background* GetInstance();

	static void ReleaseInstance();



	void Hide();

	void Show();

	void Update(int time);

	void Draw(QPainter* painter) const;

private:

	Background();

	~Background();



	/**
	* BgChar
	* ui界面背景中落下的字母
	*/
	struct BgChar
	{
		char ch;

		double x;
		double y;
		double speed;

		//不透明度
		double alpha;

		void Draw(QPainter* painter) const;
	};

	std::list<BgChar> chars;

	bool visible;

};
