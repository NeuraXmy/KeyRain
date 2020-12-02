//Particle.cpp: particle¿‡

#include "Particle.h"
#include "Define.h"

#include <qpainter.h>



Particle::Particle(
	int lifeTime,
	double resist,
	int size,
	const QColor& color,
	Vec2 pos,
	Vec2 v)
	: lifeTime(lifeTime)
	, size(size)
	, color(color)
	, pos(pos)
	, v(v)
	, resist(resist)
	, castTime(0)
	, lastFlashTime(0)
	, visible(true)
{

}

void Particle::Draw(QPainter* painter) const
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