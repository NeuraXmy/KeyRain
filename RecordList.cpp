//RecordList.cpp: 记录列表类型

#include <qpainter.h>

#include "RecordList.h"
#include "Define.h"
#include "Button.h"



RecordList::RecordList(int maxShowRecordNum)
	: Widget()
	, current(0)
	, downBtn(nullptr)
	, upBtn(nullptr)
	, maxShowRecordNum(maxShowRecordNum)
	, showingOffset(0.0)
{

}


void RecordList::Update(int time)
{
	if (downBtn)
	{
		downBtn->SetDisable(current == records.size() - 1);
	}
	if (upBtn)
	{
		upBtn->SetDisable(current == 0);
	}

	showingOffset *= 0.95;

	if (abs(showingOffset) <= 0.0001)
	{
		showingOffset = 0.0;
	}
}

void RecordList::Reset()
{
	this->Clear();
}

void RecordList::Draw(QPainter* painter) const
{
	if (!visible)
	{
		return;
	}

	//每项记录的高度
	int ItemH = h / maxShowRecordNum;

	auto font = painter->font();
	font.setPixelSize(ItemH - 1);
	painter->setFont(font);

	if (anchor == Anchor::LeftBottom)
		painter->translate(x, y);
	else if (anchor == Anchor::Center)
		painter->translate(x - w / 2, y - h / 2);

	auto trans = painter->transform();
	painter->translate(2, h);
	painter->translate(0, -showingOffset * ItemH);

	auto startEnd = GetStartEndIndex();

	for(int i = startEnd.first; i < startEnd.second; i++)
	{
		painter->setPen(current == i ? Def::recordListHighlightColor : Def::recordListColor);

		painter->translate(0, -ItemH);
		
		painter->scale(1.0, -1.0);
		painter->drawText(0, 0, records[i].c_str());
		painter->scale(1.0, -1.0);
		
	}

	painter->setTransform(trans);

	if (anchor == Anchor::LeftBottom)
		painter->translate(-x, -y);
	else if (anchor == Anchor::Center)
		painter->translate(w / 2 - x, h / 2 - y);
}



void RecordList::OnDown()
{
	auto last = GetStartEndIndex();

	if (GetCurrentIndex() < GetRecordNum() - 1)
	{
		current++;
	}

	if (GetStartEndIndex() != last)
	{
		showingOffset += 1.0;
	}
}

void RecordList::OnUp()
{
	auto last = GetStartEndIndex();

	if (GetCurrentIndex() > 0)
	{
		current--;
	}

	if (GetStartEndIndex() != last)
	{
		showingOffset -= 1.0;
	}
}

std::string RecordList::GetCurrentRecord() const
{
	if (current < 0 || current >= records.size())
	{
		return std::string();
	}
	return records[current];
}

int RecordList::GetCurrentIndex() const
{
	return current;
}

int RecordList::GetRecordNum() const
{
	return records.size();
}

std::string RecordList::GetRecord(int index) const
{
	if (index < 0 || index >= records.size())
	{
		return std::string();
	}
	return records[index];
}

void RecordList::Clear()
{
	records.clear();
	current = 0;
}

void RecordList::AddRecord(const std::string& record)
{
	records.push_back(record);
}

void RecordList::DeleteRecord(const std::string& record)
{
	auto it = std::find(records.begin(), records.end(), record);
	if (it == records.end())
	{
		return;
	}

	if (it - records.begin() < current)
	{
		current--;
	}
	records.erase(it);
}

void RecordList::DeleteRecord(int index)
{
	if (index < 0 || index >= records.size())
	{
		return;
	}

	if (index < current)
	{
		current--;
	}
	records.erase(records.begin() + index);
}

void RecordList::BindUpButton(Button* upBtn)
{
	this->upBtn = upBtn;
	connect(upBtn, &Button::ClickSignal, this, &RecordList::OnUp);
}

void RecordList::BindDownButton(Button* downBtn)
{
	this->downBtn = downBtn;
	connect(downBtn, &Button::ClickSignal, this, &RecordList::OnDown);
}

std::pair<int, int> RecordList::GetStartEndIndex() const
{
	if (maxShowRecordNum > records.size())
	{
		return std::make_pair(0, int(records.size()));
	}

	int start = std::max(0, current - maxShowRecordNum / 2);
	int end = start + maxShowRecordNum;
	
	if (end > records.size())
	{
		end = records.size();
		start = end - maxShowRecordNum;
	}
	return std::make_pair(start, end);
}
