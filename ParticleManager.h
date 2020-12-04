//ParticleManager.h: 粒子管理器类

#pragma once

#include "Particle.h"

#include <list>

class QPainter;
class QColor;



/**
* ParticleManager
* 掌管粒子的产生更新和销毁的单例类型
*/
class ParticleManager final
{
public:

	static ParticleManager* GetInstacne();

	static void ReleaseInstance();



	//获取在圆(x,y)radius=r内的随机坐标
	static Vec2 GetRandomCirclePos(double x, double y, double r);

	//获取在矩形(x1,y1)(x2,y2)内的随机坐标
	static Vec2 GetRandomSquarePos(double x1, double y1, double x2, double y2);

	//获得随机方向速度，大小从low到v
	static Vec2 GetRandomVelocity(double v, bool onlyDirRandom = true, double low = 0.0);



	//清空所有粒子
	void Clear();

	//发射粒子
	void Cast(int time, const Particle& p);

	void Update(int time);

	void Draw(QPainter* painter) const;

private:

	ParticleManager();

	~ParticleManager();

	std::list<Particle> particles;

};