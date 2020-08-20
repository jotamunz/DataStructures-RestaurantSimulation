#include "cheffthread.h"

CheffThread::CheffThread()
{

}

void CheffThread::__init__(Restaurant * _restaurant, Cheff * _cheff, QMutex * _mutexInput, QMutex * _mutexOutput, cheffForm * _cheffF, Ui::MainWindow* _mainUI)
{
    this->restaurant = _restaurant;
    this->cheff = _cheff;
    this->mutexInput = _mutexInput;
    this->mutexOutput = _mutexOutput;
    this->cheffF = _cheffF;
    this->mainUI = _mainUI;
}

void CheffThread::pause()
{
    this->paused = !paused;
}

void CheffThread::run()
{
    while(active)
    {
        if(this->cheff->cooking == false && this->getNewOrder() != nullptr)
        {
            this->cheff->cooking = true;
            qDebug().noquote() << "\t\t" << "Cheff:" << cheff->getId() << "Cocina:" << cheff->order->toString() << "por:" << cheff->order->orderedDish->prepTime;
            this->cheffF->ui->listWidget->addItem("Cheff: " + QVariant(cheff->getId()).toString() + " cocina:");
            this->cheffF->ui->listWidget->addItem("           " + cheff->order->toString() + " por: " + QVariant(cheff->order->orderedDish->prepTime).toString());
            unsigned int counter = static_cast<unsigned long>(this->cheff->order->orderedDish->prepTime);
            int sumProgressBarValue = 100/counter;
            while (counter != 0)
            {
                progressBar += sumProgressBarValue;
                sleep(1);
                counter--;
            }
            progressBar = 0;
            this->cheff->cooking = false;

            this->mutexInput->lock();
            this->cheff->order->cooking = false;
            this->cheff->order->done = true;
            qDebug().noquote() << "\t\t" << "Cheff:" << cheff->getId() << "Termina:" << cheff->order->toString();
            this->cheffF->ui->listWidget->addItem("Cheff: " + QVariant(cheff->getId()).toString() + " termina: ");
            this->cheffF->ui->listWidget->addItem("           " + cheff->order->toString());
            this->serveOrder();
            this->mutexInput->unlock();
        }
        sleep(1);
        while(this->paused)
        {
            cheff->paused = true;
            sleep(1);
        }
        cheff->paused = false;
    }
}

Order * CheffThread::getNewOrder()
{
    this->mutexInput->lock();
    Node<Queue<Order*>*> * temp = this->restaurant->kitchenRoom->kitchens[cheff->kitchenType]->InputOrders->first;
    while (temp != nullptr)
    {
        Node<Order*> * temp2 = temp->data->first;
        while (temp2 != nullptr)
        {
            if(temp2->data->cooking == false && temp2->data->done == false)
            {
                this->cheff->order = temp2->data;
                this->cheff->order->cooking = true;
                this->mutexInput->unlock();
                return cheff->order;
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    this->cheff->order = nullptr;
    this->mutexInput->unlock();
    return nullptr;
}

void CheffThread::serveOrder()
{
    Node<Order*> * temp = this->restaurant->kitchenRoom->kitchens[cheff->kitchenType]->InputOrders->first->data->first;
    bool orderDone = true;
    while (temp != nullptr)
    {
        if (temp->data->done == false)
        {
            orderDone = false;
            break;
        }
        temp = temp->next;
    }
    if (orderDone == true)
    {
        this->mutexOutput->lock();
        this->restaurant->kitchenRoom->OutputOrders->insert(this->restaurant->kitchenRoom->kitchens[cheff->kitchenType]->InputOrders->dequeue());
        qDebug().noquote() << "\t\t" << "Cheff:" << cheff->getId() << "Saca orden de mesa:" << this->restaurant->kitchenRoom->OutputOrders->last->data->last->data->tableId;
        this->cheffF->ui->listWidget->addItem("Cheff: " + QVariant(cheff->getId()).toString() + " saca orden de mesa: " + QVariant(this->restaurant->kitchenRoom->OutputOrders->last->data->last->data->tableId).toString());
        this->mutexOutput->unlock();
    }
}

void CheffThread::on_actionColas_Principales_triggered()
{

}
