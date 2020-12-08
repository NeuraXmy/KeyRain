//Background.h: ui����ı���

#pragma once

#include <list>

class QPainter;



/**
* Background
* ui���汳���ĵ�������
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
	* ui���汳�������µ���ĸ
	*/
	struct BgChar
	{
		char ch;

		double x;
		double y;
		double speed;

		//��͸����
		double alpha;

		void Draw(QPainter* painter) const;
	};

	std::list<BgChar> chars;

	bool visible;

};
