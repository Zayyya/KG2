#include "mainwindow.h"

#include <QApplication>

#pragma comment (lib, "opengl32.lib")

int main(int argc, char *argv[])
{
    std::string s;
    for (int i = 0; i < argc; i++)
        {
            if (!strcmp(argv[i], "-p") && (i + 1 < argc))
            {
                s = argv[i + 1];
            }
        }

    //QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication a(argc, argv);
    MainWindow w(nullptr, s.c_str());
    w.show();
    return a.exec();
}
