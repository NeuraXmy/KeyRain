#include "Particle.h"
#include "Define.h"

#include <qpainter.h>

#include <cmath>

void ParticleManager::Cast(int time, const Particle& p)
{
	particles.push_back(p);
	particles.back().castTime = time;
	particles.back().visible = true;
}

void ParticleManager::Update(int time)
{
	for (auto it = particles.begin(); it != particles.end(); )
	{
		if (it->castTime + it->lifeTime <= time)
		{
			if (it->castTime + it->lifeTime * 1.5 <= time)
			{
				it = particles.erase(it);
				continue;
			}
			else if (time - it->lastChangeVisTime > 20)
			{
				it->visible = Def::RandInt(0, 1);
				it->lastChangeVisTime = time;
			}
		}

		it->v.first *= (1.0 - it->resist);
		it->v.second *= (1.0 - it->resist);
		it->pos.first += it->v.first / 1000.0 * Def::tickTime;
		it->pos.second += it->v.second / 1000.0 * Def::tickTime;

		it++;
	}
}

void ParticleManager::Show(QPainter* painter)
{
	for (auto& p : particles)
	{
		p.Show(painter);
	}
}

void ParticleManager::Clear()
{
	particles.clear();
}

std::pair<double, double> GetRandomCirclePos(double x, double y, double r)
{
	double angle = Def::RandReal(0.0, Def::pi * 2.0);
	double radius = Def::RandReal(0.0, 1.0) * r;
	return std::make_pair(x + sin(angle) * radius, y + cos(angle) * radius);
}

std::pair<double, double> GetRandomSquarePos(double x1, double y1, double x2, double y2)
{
	double rx = Def::RandReal(0.0, 1.0);
	double ry = Def::RandReal(0.0, 1.0);
	return std::make_pair(x1 + (x2 - x1) * rx, y1 + (y2 - y1) * rx);
}

std::pair<double, double> GetRandomVelocity(double v, bool onlyDirRandom, double low)
{
	double angle = Def::RandReal(0.0, Def::pi * 2.0);
	double radius = (onlyDirRandom ? 1.0 : Def::RandReal(low / v, 1.0)) * v;
	return std::make_pair(sin(angle) * radius, cos(angle) * radius);
}

Particle::Particle(
	int lifeTime,
	double resist,
	int size,
	const QColor& color,
	Vec2 pos,
	Vec2 v )
	: lifeTime(lifeTime)
	, size(size)
	, color(color)
	, pos(pos)
	, v(v)
	, resist(resist)
{
	
}

void Particle::Show(QPainter* painter) const
{
	if (!visible)
	{
		return;
	}

	QPen pen = color;
	pen.setWidth(size);
	painter->setPen(pen);
	painter->drawPoint(pos.first, pos.second);
}

