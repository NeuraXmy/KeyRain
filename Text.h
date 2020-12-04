//Text.h: 文本控件类型

#pragma once

#include "Widget.h"

#include <qcolor.h>

#include <string>



/**
* Text (Widget)
* 代表ui中的文本控件类型
*/
class Text final : public  Widget
{
public:
	
	std::string str;

	QColor color;

	int fontSize;



	Text(const std::string& str = "", int fontSize = 10, const QColor color = Qt::green);


	void Draw(QPainter* painter) const override;


	void SetStr(const std::string str);

};