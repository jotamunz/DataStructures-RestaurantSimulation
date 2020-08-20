#include <QApplication>
#include "startupform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartupForm startWindow;
    startWindow.show();

    return a.exec();
}
