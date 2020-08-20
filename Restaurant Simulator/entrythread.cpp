#include "entrythread.h"

EntryThread::EntryThread()
{

}

void EntryThread::__init__(Restaurant * _restaurant, QMutex * _mutexEntry, waitingForm* _waitingF)
{
    this->restaurant = _restaurant;
    this->mutexEntry = _mutexEntry;
    this->waitingF = _waitingF;
}

void EntryThread::pause()
{
    this->paused = !paused;
}

void EntryThread::run()
{
    while (this->active)
    {
        unsigned int random = QRandomGenerator::global()->generate() % (unsigned (restaurant->entranceSecRange[1]) - unsigned (restaurant->entranceSecRange[0])) + unsigned (restaurant->entranceSecRange[0]);
        waitingF->ui->listWidget->addItem("Proximos clientes llegan en: " + QVariant(random).toString() + " segundos");
        sleep(static_cast<unsigned long>(random));
        int people = QRandomGenerator::global()->generate() % (7 - 1) + 1;
        if (isPriorityNumber(unsigned (people)) == true)
        {
            this->mutexEntry->lock();
            restaurant->waiting->priorityQueue(people);
            this->mutexEntry->unlock();
            waitingF->ui->listWidget->addItem("Llegan: " + QVariant(people).toString() + " personas con reserva");
            qDebug() << "Llegan:" << people << "personas con prioridad";
        }
        else
        {
            this->mutexEntry->lock();
            restaurant->waiting->queue(people);
            this->mutexEntry->unlock();
            waitingF->ui->listWidget->addItem("Llegan: " + QVariant(people).toString() + " personas");
            qDebug() << "Llegan:" << people << "personas";
        }
        waitingF->ui->listWidget->addItem(restaurant->waiting->toString());
        restaurant->waiting->print();       
        while(this->paused)
            sleep(1);
    }
}

bool EntryThread::isPriorityNumber(unsigned int num)
{
    for (int i = 0; i < 20; ++i)
    {
        if (restaurant->diningRoom->tables[i] != nullptr)
        {
            if(restaurant->diningRoom->tables[i]->reserved == true && restaurant->diningRoom->tables[i]->reservedAmount == num)
                return true;
        }
        else { break; }
    }
    return false;
}
