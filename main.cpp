//main.cpp： 程序入口

#include <QtWidgets/qapplication.h>

#include "Application.h"

/**
* KeyRain by NeuraXmy
* 基于Qt的下落式打字游戏
* XMU20级新生C程序设计课程期末大作业
* 项目开始于 2020/11/25
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    Application::GetInstance()->Start();

    return a.exec();
}