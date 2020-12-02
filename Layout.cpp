//Layout.cpp: ΩÁ√Ê¿‡

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
		w->Reset();
	}
}

void Layout::Exit()
{
	visible = false;
}



void Layout::Update(int time)
{
	for (auto w : widgets)
	{
		w->Update(time);
	}
}

void Layout::Draw(QPainter* painter) const
{
	if (!visible)
	{
		return;
	}

	painter->translate(x, y);
	for (auto w : widgets)
	{
		w->Draw(painter);
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



void Layout::OnKeyPressEvent(int key)
{
	for (auto w : widgets)
	{
		w->OnKeyPressEvent(key);
	}
}

void Layout::OnKeyReleaseEvent(int key)
{
	for (auto w : widgets)
	{
		w->OnKeyReleaseEvent(key);
	}
}

void Layout::OnMouseMoveEvent(int mouseX, int mouseY)
{
	for (auto w : widgets)
	{
		w->OnMouseMoveEvent(mouseX - x, mouseY - y);
	}
}

void Layout::OnMouseLeftBtnPressEvent()
{
	for (auto w : widgets)
	{
		w->OnMouseLeftBtnPressEvent();
	}
}

void Layout::OnMouseLeftBtnReleaseEvent()
{
	for (auto w : widgets)
	{
		w->OnMouseLeftBtnReleaseEvent();
	}
}
