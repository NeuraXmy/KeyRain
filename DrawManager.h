//DrawManager.h: ��ͼ����������

#pragma once

#include <qwidget.h>

/**
* DrawManager (QWidget)
* �������л�ͼ�����ĵ�������
*/
class DrawManager : public QWidget
{
	Q_OBJECT

public:

	static DrawManager* GetInstance();

	static void ReleaseInstance();

protected:

	void timerEvent(QTimerEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

private:

	DrawManager();

	~DrawManager();

	int timerId;

};
