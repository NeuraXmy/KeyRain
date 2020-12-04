//RecordList.h: 记录列表类型

#pragma once

#include "Widget.h"

#include <qcolor.h>

#include <string>
#include <vector>

class Button;



/**
* Text (Widget)
* 代表ui中的记录列表控件类型
* 可以用以记录展示或选择
*/
class RecordList final : public  Widget
{
public:

	RecordList(int maxShowRecordNum);



	void Update(int time) override;

	void Reset() override;

	void Draw(QPainter* painter) const override;



	//向下一条记录
	void OnDown();

	//向上一条记录
	void OnUp();



	//获取当前记录
	std::string GetCurrentRecord() const;

	//获取当前记录是第几条
	int GetCurrentIndex() const;

	//获取当前总记录条数
	int GetRecordNum() const;

	//获取某个索引下的记录
	std::string GetRecord(int index) const;

	//清空记录
	void Clear();

	//加入记录
	void AddRecord(const std::string& record);

	//删除记录（如果存在）
	void DeleteRecord(const std::string& record);

	//删除某个索引下的记录
	void DeleteRecord(int index);

	//绑定向上的按钮
	void BindUpButton(Button* upBtn);

	//绑定向下的按钮
	void BindDownButton(Button* downBtn);

private:

	//当前的记录索引
	int current;

	//显示中的偏移
	double showingOffset;

	//最多显示的记录数
	int maxShowRecordNum;

	std::vector<std::string> records;

	Button* upBtn;

	Button* downBtn;

	//获取显示中的开始索引和结束索引
	std::pair<int, int> GetStartEndIndex() const;

};