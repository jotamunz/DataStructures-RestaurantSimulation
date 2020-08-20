#include "refreshthread.h"
#include <QtCore>

refreshThread::refreshThread(QObject * parent) :
    QThread(parent)
{    
}

void refreshThread::run()
{
    while(true){
        emit refresh();
        sleep(1);
    }
}

