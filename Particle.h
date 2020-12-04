//Particle.h: particle类

#pragma once

#include <list>

#include <qcolor.h>

using Vec2 = std::pair<double, double>;

class QPainter;



/**
* Particle
* 游戏中单个粒子的类型
*/
struct Particle final
{
	bool visible;

	int lifeTime;
	int castTime;

	int size;
	QColor color;

	Vec2 pos;
	Vec2 v;

	//粒子速度递减的系数
	double resist;
	//上次闪烁的时间
	int lastFlashTime;

	Particle(
		int lifeTime,
		double resist = 0.0,
		int size = 0,
		const QColor& color = QColor(),
		Vec2 pos = std::make_pair(0.0, 0.0),
		Vec2 v   = std::make_pair(0.0, 0.0)
	);

	void Draw(QPainter* painter) const;
};