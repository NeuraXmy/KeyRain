//main.cpp�� �������

#include <QtWidgets/qapplication.h>

#include "Define.h"
#include "Application.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    Application::GetInstance()->Start();

    return a.exec();
}