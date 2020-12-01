#include "UiManager.h"
#include "Layout.h"
#include "Define.h"
#include "Widget.h"

#include <qpainter.h>

Layout::Layout()
	: x(0)
	, y(0)
	, visible(false)
{

}

Layout::~Layout()
{
	ClearWidget();
}

void Layout::Enter()
{
	visible = true;
	for (auto w : widgets)
	{
		w->blockSignals(false);
	}
}

void Layout::Exit()
{
	visible = false;
	for (auto w : widgets)
	{
		w->blockSignals(true);
	}
}

void Layout::Update(int time)
{
	for (auto w : widgets)
	{
		w->Update(time);
	}
}

void Layout::Show(QPainter* painter) const
{
	if (!visible)
	{
		return;
	}

	painter->translate(x, y);
	for (auto w : widgets)
	{
		w->Show(painter);
	}
	painter->translate(-x, -y);
}

void Layout::AddWidget(Widget* w)
{
	widgets.push_back(w);
}

void Layout::ClearWidget()
{
	for (auto w : widgets)
	{
		delete w;
	}
	widgets.clear();
}
