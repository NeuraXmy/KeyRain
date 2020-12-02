//Note.cpp： 字符类及字符的状态属性

#include "Note.h"
#include "Define.h"

#include <qpainter.h>
#include <qfontmetrics.h>



Note::Note(char ch, double x, double y, bool wordBegin)
	: ch(ch)
	, x(x)
	, y(y)
	, stat(NoteStat::hidden)
	, wordBegin(wordBegin)
	, particleColor()
	, lastCastDragParticleTime()
	, bonus(BonusMode::noBonus)
{

}

void Note::Draw(QPainter* painter, bool is1st, bool fever) const
{
	if (stat != NoteStat::visible)
	{
		return;
	}

	QString text(1, toupper(ch));
	QFontMetrics m(painter->font());
	int fontSizeX = m.width(text);
	int fontSizeY = m.height();

	painter->translate(x, y);

	int r, g, b;
	double fstFactor;

	if (!fever)
	{
		fstFactor = is1st ? 1.5 : 1.0;
		if (bonus)
		{
			r = std::min(255.0, 100 * fstFactor);
			g = std::min(255.0, 100 * fstFactor);
			b = std::min(255.0, 255 * fstFactor);
		}
		else
		{
			double yFactor = y / double(Def::trackHeight);
			r = std::min(255.0, ((1.0 - yFactor) * 200 + 55) * fstFactor);
			g = std::min(255.0, (yFactor * 200 + 55) * fstFactor);
			b = std::min(255.0, 40 * fstFactor);
		}
	}
	else
	{
		fstFactor = is1st ? 1.5 : 0.8;
		r = std::min(255.0, QColor(Qt::yellow).red()	* fstFactor);
		g = std::min(255.0, QColor(Qt::yellow).green()	* fstFactor);
		b = std::min(255.0, QColor(Qt::yellow).blue()	* fstFactor);
	}
	
	particleColor = QColor(r * 0.8, g * 0.8, b * 0.8);
	
	painter->setPen(QColor(r, g, b));

	painter->scale(1.0, -1.0);
	painter->drawText(-fontSizeX / 2, fontSizeY / 2 - 5, text);
	painter->scale(1.0, -1.0);

	painter->translate(-x, -y);
}
