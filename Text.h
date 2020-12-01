#pragma once
#include "Widget.h"

#include <qcolor.h>

#include <string>

class Text : public  Widget
{
public:
	
	std::string str;

	QColor color;

	int fontSize;


	Text(const std::string& str = "", int fontSize = 10, const QColor color = Qt::green);

	void Update(int time) override;

	void Show(QPainter* painter) const override;

};