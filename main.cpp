//main.cpp£º ³ÌĞòÈë¿Ú

#include <QtWidgets/qapplication.h>

#include "Application.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    Application::GetInstance()->Start();

    return a.exec();
}