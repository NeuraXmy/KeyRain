#pragma once

#include <qcolor.h>

#include <list>

using Vec2 = std::pair<double, double>;

Vec2 GetRandomCirclePos(double x, double y, double r);

Vec2 GetRandomSquarePos(double x1, double y1, double x2, double y2);

Vec2 GetRandomVelocity(double v, bool onlyDirRandom = true, double low = 0.0);


class QPainter;

struct Particle
{
	int lifeTime;
	int castTime;
	int size;
	QColor color;
	Vec2 pos;
	Vec2 v;
	double resist;

	bool visible;
	int lastChangeVisTime;

	Particle(
		int lifeTime, 
		double resist = 0.0,
		int size = 0, 
		const QColor& color = QColor(), 
		Vec2 pos = std::make_pair(0.0, 0.0), 
		Vec2 v = std::make_pair(0.0, 0.0) 
	);

	void Show(QPainter* painter) const;
};

class ParticleManager
{
public:

	void Cast(int time, const Particle& p);

	void Update(int time);

	void Show(QPainter* painter);

	void Clear();

private:

	std::list<Particle> particles;

};