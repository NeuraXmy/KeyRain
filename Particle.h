//Particle.h: particle��

#pragma once

#include <list>

#include <qcolor.h>

using Vec2 = std::pair<double, double>;

class QPainter;



/**
* Particle
* ��Ϸ�е������ӵ�����
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

	//�����ٶȵݼ���ϵ��
	double resist;
	//�ϴ���˸��ʱ��
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