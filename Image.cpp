//Image.cpp: 图片控件类型

#include "Image.h"

#include <qpainter.h>

Image::Image(const std::string& path)
	: Widget()
	, image(nullptr)
	, imageLoadFromFile(false)
{
	LoadImage(path);
}



void Image::Draw(QPainter* painter) const
{
	if (!visible || !image)
	{
		return;
	}

	if (anchor == Anchor::LeftBottom)
		painter->translate(x, y);
	else if (anchor == Anchor::Center)
		painter->translate(x - w / 2, y - h / 2);

	painter->scale(1.0, -1.0);
	painter->drawImage(QRect(0, -h, w, h), *image);
	painter->scale(1.0, -1.0);

	if (anchor == Anchor::LeftBottom)
		painter->translate(-x, -y);
	else if (anchor == Anchor::Center)
		painter->translate(w / 2 - x, h / 2 - y);
}



void Image::SetImage(const std::string& path)
{
	ReleaseImage();
	LoadImage(path);
}

void Image::SetImage(QImage* image)
{
	ReleaseImage();
	this->image = image;
}

void Image::LoadImage(const std::string& path)
{
	image = new QImage(path.c_str());
	imageLoadFromFile = true;

	if (image->isNull())
	{
		ReleaseImage();
	}
}

void Image::ReleaseImage()
{
	if (imageLoadFromFile)
	{
		delete image;
		imageLoadFromFile = false;
	}
	image = nullptr;
}
