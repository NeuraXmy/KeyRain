//ParticleManager.cpp: 粒子管理器类与几个计算粒子随机性的函数

#include "ParticleManager.h"
#include "Particle.h"
#include "Define.h"
#include "Settings.h"

#include <qpainter.h>

#include <cmath>

namespace
{
	ParticleManager* instance = nullptr;
}

ParticleManager* ParticleManager::GetInstacne()
{
	if (!instance)
	{
		instance = new ParticleManager();
	}
	return instance;
}

void ParticleManager::ReleaseInstance()
{
	if (instance)
	{
		delete instance;
	}
}



ParticleManager::ParticleManager()
{

}

ParticleManager::~ParticleManager()
{

}



void ParticleManager::Clear()
{
	particles.clear();
}

void ParticleManager::Cast(int time, const Particle& p)
{
	if (!Settings::GetInstance()->showParticle)
	{
		return;
	}

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
				//超过生存时间的1.5倍就清除粒子
				it = particles.erase(it);
				continue;
			}
			else if (time - it->lastFlashTime > Def::particleFlashInterval)
			{
				//超过生存时间粒子开始闪烁
				it->visible = Def::RandInt(0, 1);
				it->lastFlashTime = time;
			}
		}

		//更新粒子的物理信息
		it->v.first *= (1.0 - it->resist);
		it->v.second *= (1.0 - it->resist);
		it->pos.first += it->v.first / 1000.0 * Def::gameTick;
		it->pos.second += it->v.second / 1000.0 * Def::gameTick;

		it++;
	}
}

void ParticleManager::Draw(QPainter* painter) const
{
	painter->translate(Def::trackPosX, Def::trackPosY);

	for (auto& p : particles)
	{
		p.Draw(painter);
	}

	painter->translate(-Def::trackPosX, -Def::trackPosY);
}



Vec2 ParticleManager::GetRandomCirclePos(double x, double y, double r)
{
	double angle = Def::RandReal(0.0, Def::pi * 2.0);
	double radius = Def::RandReal(0.0, 1.0) * r;
	return std::make_pair(x + sin(angle) * radius, y + cos(angle) * radius);
}

Vec2 ParticleManager::GetRandomSquarePos(double x1, double y1, double x2, double y2)
{
	double rx = Def::RandReal(0.0, 1.0);
	double ry = Def::RandReal(0.0, 1.0);
	return std::make_pair(x1 + (x2 - x1) * rx, y1 + (y2 - y1) * rx);
}

Vec2 ParticleManager::GetRandomVelocity(double v, bool onlyDirRandom, double low)
{
	double angle = Def::RandReal(0.0, Def::pi * 2.0);
	double radius = (onlyDirRandom ? 1.0 : Def::RandReal(low / v, 1.0)) * v;
	return std::make_pair(sin(angle) * radius, cos(angle) * radius);
}