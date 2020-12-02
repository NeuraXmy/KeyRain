//Image.h: 图片控件类型

#pragma once

#include "Widget.h"

#include <string>

class QImage;
class QPainter;



/**
* Image (Widget)
* 代表ui中的图片控件类型
*/
class Image : public  Widget
{
public:

	Image(const std::string& path = "");


	void Draw(QPainter* painter) const override;


	void SetImage(const std::string& path);

	void SetImage(QImage* image);
	
private:

	QImage* image;

	bool imageLoadFromFile;


	void LoadImage(const std::string& path);

	void ReleaseImage();

};