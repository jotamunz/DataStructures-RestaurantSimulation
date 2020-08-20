#include "dishwasherthread.h"

DishWasherThread::DishWasherThread()
{

}

void DishWasherThread::__init__(Restaurant * _restaurant, QMutex * _mutexDishes, dishwasherForm * _dishwasherF, Ui::MainWindow * _mainUI)
{
    this->restaurant = _restaurant;
    this->mutexDishes = _mutexDishes;
    this->dishwasherF = _dishwasherF;
    this->mainUI = _mainUI;
}

void DishWasherThread::pause()
{
    this->paused = !paused;
}

void DishWasherThread::run()
{
    int count = 0;
    while(active)
    {
        if(!restaurant->kitchenRoom->dishPile->isEmpty())
        {
            mutexDishes->lock();
            Order * dish = restaurant->kitchenRoom->dishPile->dequeue();
            mutexDishes->unlock();
            sleep(static_cast<unsigned long>(dish->orderedDish->washTime));
            count++;
            qDebug() << "Platos lavados:" << count;
            this->mainUI->label_DishWasher->setNum(count);
            this->dishwasherF->ui->listWidget->addItem("Lavando:");
            this->dishwasherF->ui->listWidget->addItem("           " + dish->toString() + " por: " + QVariant(dish->orderedDish->washTime).toString());
            this->dishwasherF->ui->listWidget->addItem("Total de platos lavados: " + QVariant(count).toString());
        }
        else
            sleep(1);
        while(this->paused)
            sleep(1);
    }
}
