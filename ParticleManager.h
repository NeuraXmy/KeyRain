//ParticleManager.h: ���ӹ�������

#pragma once

#include "Particle.h"

#include <list>

class QPainter;
class QColor;



/**
* ParticleManager
* �ƹ����ӵĲ������º����ٵĵ�������
*/
class ParticleManager final
{
public:

	static ParticleManager* GetInstacne();

	static void ReleaseInstance();



	//��ȡ��Բ(x,y)radius=r�ڵ��������
	static Vec2 GetRandomCirclePos(double x, double y, double r);

	//��ȡ�ھ���(x1,y1)(x2,y2)�ڵ��������
	static Vec2 GetRandomSquarePos(double x1, double y1, double x2, double y2);

	//�����������ٶȣ���С��low��v
	static Vec2 GetRandomVelocity(double v, bool onlyDirRandom = true, double low = 0.0);



	//�����������
	void Clear();

	//��������
	void Cast(int time, const Particle& p);

	void Update(int time);

	void Draw(QPainter* painter) const;

private:

	ParticleManager();

	~ParticleManager();

	std::list<Particle> particles;

};