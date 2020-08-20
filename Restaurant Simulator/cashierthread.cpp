#include "cashierthread.h"

CashierThread::CashierThread()
{

}

void CashierThread::__init__(Restaurant * _restaurant, QMutex * _mutexBills, cashierForm * _cashierF, Ui::MainWindow * _mainUI)
{
    this->restaurant = _restaurant;
    this->mutexBills = _mutexBills;
    this->cashierF = _cashierF;
    this->mainUI = _mainUI;
}

void CashierThread::pause()
{
    this->paused = !paused;
}
void CashierThread::run()
{
    int orderCount = 0;
    int moneyCount = 0;
    int billCount = 0;
    while(active)
    {
        if(!restaurant->diningRoom->bills->isEmpty())
        {
            Queue<Order*> * tableBill = new Queue<Order*>();
            mutexBills->lock();
            if (restaurant->diningRoom->bills->stack == true)
                tableBill = restaurant->diningRoom->bills->pop();
            else
                tableBill = restaurant->diningRoom->bills->dequeue();
            mutexBills->unlock();
            Node<Order*> * temp = tableBill->first;
            this->cashierF->ui->listWidget->addItem("Cobrando:");
            while (temp != nullptr)
            {
                orderCount++;
                moneyCount += temp->data->orderedDish->price;
                billCount += temp->data->orderedDish->price;
                this->mainUI->label_Cashier->setText("₡" + QVariant(moneyCount).toString());
                this->cashierF->ui->listWidget->addItem("           " + temp->data->toString());
                sleep(1);
                temp = temp->next;
            }
            this->cashierF->ui->listWidget->addItem("Total de la cuenta: " + QVariant(billCount).toString());
            billCount = 0;
            this->cashierF->ui->listWidget->addItem("Ordenes vendidas: " + QVariant(orderCount).toString() + " por un total de: " + QVariant(moneyCount).toString());
            qDebug() << "Ordenes vendidas:" << orderCount << "Por un total de:" << moneyCount;
        }
        sleep(1);
        while(this->paused)
                sleep(1);
    }
}
