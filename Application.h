//Application.h: Ӧ�ó���������

#pragma once

#include <qwidget.h>

/**
* Application (QWidget)
* Ӧ�ó��������ĵ�������
* �ƹܸ��ֹ���������
*/
class Application : public QWidget
{
	Q_OBJECT

public:

	static Application* GetInstance();

	static void ReleaseInstance();
	

	//����Ӧ�ó���
	void Start();

private:

	Application();

	~Application();

	//��ʼ������������źŲ�����
	void InitSingalSlots();

};
