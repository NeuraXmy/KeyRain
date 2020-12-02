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

signals:

	void WindowCloseSignal();

protected:

	void timerEvent(QTimerEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

	void closeEvent(QCloseEvent* event) override;

private:

	DrawManager();

	~DrawManager();

	int timerId;

};
