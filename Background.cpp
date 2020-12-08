//Background.cpp: ui界面的背景

#include "Background.h"
#include "Define.h"
#include "Settings.h"

#include <qpainter.h>
#include <cmath>



namespace
{
	Background* instance = nullptr;
}

Background* Background::GetInstance()
{
	if (!instance)
	{
		instance = new Background();
	}
	return instance;
}

void Background::ReleaseInstance()
{
	if (instance)
	{
		delete instance;
	}
}


Background::Background()
	: visible(true)
{
	for (int i = 0; i < Def::bgCharNum; i++)
	{
		BgChar ch;
		ch.ch = Def::RandInt('a', 'z');
		ch.x = Def::RandInt(30, Def::trackWidth - 30);
		ch.y = Def::RandInt(30, Def::trackHeight + 30);
		ch.speed = Def::bgCharSpeed * Def::RandReal(0.5, 2.0);
		chars.push_back(ch);
	}
}

Background::~Background()
{
	chars.clear();
}



void Background::Hide()
{
	visible = false;
}

void Background::Show()
{
	visible = true;
}

void Background::Update(int time)
{
	if (!visible || !Settings::GetInstance()->showParticle)
	{
		return;
	}

	for (auto& ch : chars)
	{
		ch.y -= ch.speed / 1000.0 * Def::uiTick;

		ch.alpha = (std::sin(time / 500.0 + ch.x) + 1.0) * 0.2;

		//下落到底
		if (ch.y < -30)
		{
			ch.ch = Def::RandInt('a', 'z');
			ch.x = Def::RandInt(30, Def::trackWidth - 30);
			ch.y = Def::trackHeight + 30;
			ch.speed = Def::bgCharSpeed * Def::RandReal(0.8, 1.2);
		}
	}
}

void Background::Draw(QPainter* painter) const
{
	if (!visible || !Settings::GetInstance()->showParticle)
	{
		return;
	}

	auto font = painter->font();
	font.setPixelSize(Def::noteSize * Settings::GetInstance()->noteScale);
	font.setBold(false);
	painter->setFont(font);

	for (auto& ch : chars)
	{
		ch.Draw(painter);
	}
}



void Background::BgChar::Draw(QPainter* painter) const
{
	//计算字符大小，居中显示

	QString text(1, toupper(ch));
	QFontMetrics m(painter->font());
	int fontSizeX = m.width(text);
	int fontSizeY = m.height();

	painter->translate(x, y);

	QColor color = { 0, int(255 * alpha), 0 };

	painter->setPen(color);

	painter->scale(1.0, -1.0);
	painter->drawText(-fontSizeX / 2, fontSizeY / 2 - 5, text);
	painter->scale(1.0, -1.0);

	painter->translate(-x, -y);
}
