#include "assignerthread.h"

AssignerThread::AssignerThread()
{

}

void AssignerThread::__init__(Restaurant * _restaurant, QMutex * _mutexEntry,assignerForm * _assignerF, tableForm * _tableF)
{
    this->restaurant = _restaurant;
    this->mutexEntry = _mutexEntry;
    this->tableF = _tableF;
    this->assignerF = _assignerF;
}

void AssignerThread::pause()
{
    this->paused = !paused;
}

void AssignerThread::run()
{
    int clientCount = 0;
    while (this->active)
    {
        if (!(restaurant->waiting->isEmpty()))
        {
            if (isPriorityNumber(unsigned(restaurant->waiting->peek())))
            {
                this->mutexEntry->lock();
                int clientAmount = restaurant->waiting->dequeue();
                this->mutexEntry->unlock();
                int freeTable = getReservedTable(unsigned (clientAmount));
                this->assignerF->ui->listWidget->addItem("Se sientan: " + QVariant(clientAmount).toString() + " clientes con reserva a mesa: " + QVariant(freeTable).toString());
                qDebug() << "Agregar:" << clientAmount << "clientes de prioridad a mesa:" << freeTable;
                restaurant->diningRoom->addClientGroup(clientAmount, clientCount, freeTable, restaurant->entrySecRange, restaurant->mainSecRange, restaurant->dessertSecRange, restaurant->arrayPercetages, restaurant->menu);
                restaurant->diningRoom->tables[freeTable]->setTableEats();
                restaurant->diningRoom->tables[freeTable]->setTableWaitingTimes();
                this->tableF->ui->listWidget->addItem("Info: " + restaurant->diningRoom->tables[freeTable]->toString());
                qDebug().noquote() << "\t" << restaurant->diningRoom->tables[freeTable]->toString();
                restaurant->diningRoom->tables[freeTable]->unReserveTable();
                clientCount += clientAmount;
            }
            else
            {
                int freeTable = restaurant->diningRoom->freeTableNumber();
                if (freeTable != -1)
                {
                    this->mutexEntry->lock();
                    int clientAmount = restaurant->waiting->dequeue();
                    this->mutexEntry->unlock();
                    this->assignerF->ui->listWidget->addItem("Se sientan: " + QVariant(clientAmount).toString() + " clientes a mesa: " + QVariant(freeTable).toString());
                    qDebug() << "Agregar:" << clientAmount << "clientes a mesa:" << freeTable;
                    restaurant->diningRoom->addClientGroup(clientAmount, clientCount, freeTable, restaurant->entrySecRange, restaurant->mainSecRange, restaurant->dessertSecRange, restaurant->arrayPercetages, restaurant->menu);
                    restaurant->diningRoom->tables[freeTable]->setTableEats();
                    restaurant->diningRoom->tables[freeTable]->setTableWaitingTimes();
                    this->tableF->ui->listWidget->addItem("Info mesa: " + QVariant(freeTable).toString() + " " + restaurant->diningRoom->tables[freeTable]->toString());
                    qDebug().noquote() << "\t" << restaurant->diningRoom->tables[freeTable]->toString();
                    clientCount += clientAmount;
                }
            }
        }
        sleep(1);
        while(this->paused)
            sleep(1);
    }
}

bool AssignerThread::isPriorityNumber(unsigned int reserveNum)
{
    for (int i = 0; i < 20; ++i)
    {
        if (restaurant->diningRoom->tables[i] != nullptr)
        {
            if(restaurant->diningRoom->tables[i]->reserved == true && restaurant->diningRoom->tables[i]->reservedAmount == reserveNum)
                return true;
        }
        else { break; }
    }
    return false;
}

int AssignerThread::getReservedTable(unsigned int reserveNum)
{
    for (int i = 0; i < 20; ++i)
    {
        if (restaurant->diningRoom->tables[i] != nullptr)
        {
            if(restaurant->diningRoom->tables[i]->reserved == true && restaurant->diningRoom->tables[i]->reservedAmount == reserveNum)
                return i;
        }
        else { break; }
    }
    return -1;
}
