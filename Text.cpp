#include "Text.h"

#include <qpainter.h>

Text::Text(const std::string& str, int fontSize, const QColor color)
	: Widget()
	, str(str)
	, fontSize(fontSize)
	, color(color)
{

}

void Text::Update(int time)
{

}

void Text::Show(QPainter* painter) const
{
	if (!visible)
	{
		return;
	}

	painter->setPen(color);

	auto font = painter->font();
	font.setPixelSize(fontSize);
	painter->setFont(font);

	QFontMetrics m(painter->font());
	int fontW = m.width(str.c_str());
	int fontH = m.height();
	
	if (anchor == Anchor::LeftBottom)
		painter->translate(x, y);
	else if(anchor == Anchor::Center)
		painter->translate(x - fontW / 2, y - fontH / 2);

	painter->scale(1.0, -1.0);
	painter->drawText(0, 0, str.c_str());
	painter->scale(1.0, -1.0);

	if (anchor == Anchor::LeftBottom)
		painter->translate(-x, -y);
	else if (anchor == Anchor::Center)
		painter->translate(fontW / 2 - x, fontH / 2 - y);
}
