//Layout.cpp: 界面类

#include "Layout.h"
#include "Define.h"
#include "Widget.h"

#include <qpainter.h>

Layout::Layout()
	: x(0)
	, y(-Def::trackHeight)
	, visible(false)
{

}

Layout::~Layout()
{
	ClearWidget();
}



void Layout::Enter(bool withAnimation)
{
	visible = true;
	y = Def::trackHeight;

	if (!withAnimation)
	{
		y = 0;
	}

	for (auto w : widgets)
	{
		w->Reset();
	}
}

void Layout::Exit(bool withAnimation)
{
	visible = false;

	if (!withAnimation)
	{
		y = -Def::trackHeight;
	}
}



void Layout::Update(int time)
{
	if (visible && y > 0)
	{
		//从上方落下进入
		y += (-y - 10) * 0.2;
		if (y < 1.0)
		{
			y = 0.0;
		}
	}
	if (!visible && y > -Def::trackHeight)
	{
		//落到下方退出
		y += (-Def::trackHeight - y - 10) * 0.2;
		if (y - -Def::trackHeight < 1.0)
		{
			y = -Def::trackHeight;
		}
	}

	if (visible)
	{
		for (auto w : widgets)
		{
			w->Update(time);
		}
	}
}

void Layout::Draw(QPainter* painter) const
{
	if (y <= -Def::trackHeight)
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
