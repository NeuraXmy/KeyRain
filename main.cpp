#include <QtWidgets/qapplication.h>
#include <qfontdatabase.h>
#include <qdebug.h>
#include <qdatetime.h>

#include "Game.h"
#include "Define.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Def::SetRandSeed(QDateTime::currentDateTime().time().msec());

    int fontId = QFontDatabase::addApplicationFont((Def::resPath + "font/Freon.ttf").c_str());
    QStringList fontIDs = QFontDatabase::applicationFontFamilies(fontId);
    if (!fontIDs.isEmpty())
    {
        QFont font(fontIDs.first());
        QApplication::setFont(font);
    }
    else
    {
        qDebug() << "[ERR] Failed to load font";
    }
   
    Game game;

    game.show();

    game.Start("cppkeywords");

    return a.exec();
}
