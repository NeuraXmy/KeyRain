//Image.h: ͼƬ�ؼ�����

#pragma once

#include "Widget.h"

#include <string>

class QImage;
class QPainter;



/**
* Image (Widget)
* ����ui�е�ͼƬ�ؼ�����
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