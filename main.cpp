//main.cpp�� �������

#include <QtWidgets/qapplication.h>

#include "Application.h"

/**
* KeyRain by NeuraXmy
* ����Qt������ʽ������Ϸ
* XMU20������C������ƿγ���ĩ����ҵ
* ��Ŀ��ʼ�� 2020/11/25
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    Application::GetInstance()->Start();

    return a.exec();
}