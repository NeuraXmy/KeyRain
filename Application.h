//Application.h: 应用程序主体类

#pragma once

#include <qwidget.h>

/**
* Application (QWidget)
* 应用程序的主体的单例类型
* 掌管各种管理器类型
*/
class Application final : public QWidget
{
	Q_OBJECT

public:

	static Application* GetInstance();

	static void ReleaseInstance();
	

	//启动应用程序
	void Start();

	//结束应用程序
	void Exit();

private:

	Application();

	~Application();

	//初始化管理器间的信号槽连接
	void InitSingalSlots();

};

