//Application.h: Ӧ�ó���������

#pragma once

#include <qwidget.h>

/**
* Application (QWidget)
* Ӧ�ó��������ĵ�������
* �ƹܸ��ֹ���������
*/
class Application final : public QWidget
{
	Q_OBJECT

public:

	static Application* GetInstance();

	static void ReleaseInstance();
	

	//����Ӧ�ó���
	void Start();

	//����Ӧ�ó���
	void Exit();

private:

	Application();

	~Application();

	//��ʼ������������źŲ�����
	void InitSingalSlots();

};

