#include "waiterthread.h"

WaiterThread::WaiterThread()
{

}

void WaiterThread::__init__(Restaurant * _restaurant, Waiter * _waiter, QMutex * _mutexOutput, QMutex * _mutexDishes, QMutex * _mutexInput0, QMutex * _mutexInput1, QMutex * _mutexInput2, QMutex * _mutexBills, waiterForm * _waiterF, queueForm * _queueF)
{
    this->restaurant = _restaurant;
    this->waiter = _waiter;
    this->mutexOutput = _mutexOutput;
    this->mutexDishes = _mutexDishes;
    this->mutexInputs[0] = _mutexInput0;
    this->mutexInputs[1] = _mutexInput1;
    this->mutexInputs[2] = _mutexInput2;
    this->mutexBills = _mutexBills;
    this->waiterF = _waiterF;
    this->queueF = _queueF;
}

void WaiterThread::pause()
{
    this->paused = !paused;
}

void WaiterThread::run()
{
    while (this->active)
    {
        for(int i = waiter->indexStart; i <= waiter->indexEnd; i++) //tables
        {
            waiter->tableId = i;
            Table * tempTable = restaurant->diningRoom->tables[i];
            if(tempTable->isEmpty() == false && tempTable->readyToOrder == true && tempTable->paying == false)
            {
                tempTable->beingAttended = true;
                waiter->attending = true;
                tempTable->changePhase();
                sleep(static_cast<unsigned long>(restaurant->walkingTime));
                if (!tempTable->dirtyDishes->isEmpty()) //vaciar platos sucios
                {
                    qDebug() << "Mesero:" << waiter->id << "Recoge los platos de mesa:" << tempTable->id;
                    this->waiterF->ui->listWidget->addItem("Mesero: " + QVariant(waiter->id).toString() + " recoge los platos de mesa: " + QVariant(tempTable->id).toString());
                    waiter->clearingDishes = true;
                    sleep(static_cast<unsigned long>(restaurant->walkingTime));
                    waiter->clearingDishes = false;
                    mutexDishes->lock();
                    while(!tempTable->dirtyDishes->isEmpty())
                        restaurant->kitchenRoom->dishPile->queue(tempTable->dirtyDishes->dequeue());
                    mutexDishes->unlock();
                    sleep(static_cast<unsigned long>(restaurant->walkingTime));
                }
                if (tempTable->phase < 3) //order
                {
                    waiter->takingOrder = true;
                    waiter->newOrders = new Queue<Order*>();
                    this->waiterF->ui->listWidget->addItem("Mesero: " + QVariant(waiter->id).toString() + " toma la orden de mesa: " + QVariant(tempTable->id).toString());
                    qDebug() << "Mesero:" << waiter->id << "Toma la orden de mesa:" << tempTable->id;
                    for(int j = 0; j < 6; j++) //clients
                    {
                        if(tempTable->clients[j] != nullptr)
                        {
                            waiter->generateOrder(tempTable->clients[j],tempTable->phase,tempTable,waiterF);
                            sleep(static_cast<unsigned long>(restaurant->orderTakingTime));
                        }
                    }
                    tempTable->dirtyDishes = waiter->newOrders;
                    tempTable->readyToOrder = false;
                    sleep(static_cast<unsigned long>(restaurant->walkingTime));
                    waiter->takingOrder = false;
                    this->mutexInputs[tempTable->phase]->lock();
                    restaurant->kitchenRoom->kitchens[tempTable->phase]->InputOrders->queue(waiter->newOrders);
                    this->mutexInputs[tempTable->phase]->unlock();
                }
                else //pay and leave
                {
                    waiterF->ui->listWidget->addItem("Mesero: " + QVariant(waiter->id).toString() + " toma el pago de mesa: " + QVariant(tempTable->id).toString());
                    qDebug() << "Mesero:" << waiter->id << "Toma el pago de mesa:" << tempTable->id;
                    tempTable->paying = true;
                    waiter->takingBill = true;
                    sleep(static_cast<unsigned long>(restaurant->walkingTime));
                    waiter->takingBill = false;
                    mutexBills->lock();
                    restaurant->diningRoom->bills->queueORpush(tempTable->tableBill);
                    mutexBills->unlock();
                }
                waiter->attending = false;
                tempTable->beingAttended = false;
            }
        }
        waiter->newOrders = pickOrder(); //buscar platos listos
        if(waiter->newOrders != nullptr)
        {
            waiter->takingDishes = true;
            waiter->tableId = waiter->newOrders->first->data->tableId;
            waiterF->ui->listWidget->addItem("Mesero: " + QVariant(waiter->id).toString() + " lleva la orden a mesa: " + QVariant(waiter->tableId).toString());
            qDebug() << "Mesero:" << waiter->id << "Lleva la orden a mesa:" << waiter->tableId;
            sleep(static_cast<unsigned long>(restaurant->walkingTime));
            restaurant->diningRoom->tables[waiter->tableId]->eating = true;
            waiter->takingDishes = false;
        }
        //updateQueueForm(queueF, mutexInputs[0], mutexInputs[1], mutexInputs[2], mutexOutput, mutexDishes, mutexBills);
        sleep(1);
        while(this->paused)
        {
            waiter->paused = true;
            sleep(1);
        }
        waiter->paused = false;
    }
}

Queue<Order*>* WaiterThread::pickOrder()
{
    this->mutexOutput->lock();
    for(int i = waiter->indexStart; i <= waiter->indexEnd; i++) //tables
    {
        if(!restaurant->kitchenRoom->OutputOrders->isEmpty())
        {
            Node<Queue<Order*>*> * temp = restaurant->kitchenRoom->OutputOrders->first;
            while(temp != nullptr)
            {
                if(temp->data->first->data->tableId == i) // desconectar el nodo
                {
                    if(restaurant->kitchenRoom->OutputOrders->first == restaurant->kitchenRoom->OutputOrders->last) // un elemento
                        restaurant->kitchenRoom->OutputOrders->first = restaurant->kitchenRoom->OutputOrders->last = nullptr; 
                    else if(temp == restaurant->kitchenRoom->OutputOrders->first) // primero de la lista
                    {
                        restaurant->kitchenRoom->OutputOrders->first = temp->next;
                        temp->next = nullptr;
                    }
                    else if(temp == restaurant->kitchenRoom->OutputOrders->last) // ultimo de la lista
                    {
                        Node<Queue<Order*>*> * temp2 = restaurant->kitchenRoom->OutputOrders->first;
                        while(temp2 != nullptr && temp2->next != temp)
                            temp2 = temp2->next;
                        restaurant->kitchenRoom->OutputOrders->last = temp2;
                        temp2->next = nullptr;
                    }
                    else // medio de la lista
                    {
                        Node<Queue<Order*>*> * temp2 = restaurant->kitchenRoom->OutputOrders->first;
                        while(temp2 != nullptr && temp2->next != temp)
                            temp2 = temp2->next;
                        temp2->next = temp->next;
                        temp->next = nullptr;
                    }
                    this->mutexOutput->unlock();
                    return temp->data;
                }
                temp = temp->next;
            }
        }
    }
    this->mutexOutput->unlock();
    return nullptr;
}

void WaiterThread::updateQueueForm(queueForm * queueF, QMutex * mutexInput0, QMutex * mutexInput1, QMutex * mutexInput2, QMutex * mutexOutput, QMutex * mutexDishes, QMutex * mutexBills)
{
    mutexInput0->lock();
    mutexInput1->lock();
    mutexInput2->lock();
    mutexOutput->lock();
    mutexDishes->lock();
    mutexBills->lock();
    queueF->ui->listWidget_Input->clear();
    queueF->ui->listWidget_Output->clear();
    queueF->ui->listWidget_Dishes->clear();
    queueF->ui->listWidget_Bills->clear();
    if (!restaurant->kitchenRoom->kitchens[0]->InputOrders->isEmpty())
    {
        Node<Queue<Order*>*>* temp = restaurant->kitchenRoom->kitchens[0]->InputOrders->first;
        while (temp != nullptr)
        {
            Node<Order*>* temp2 = temp->data->first;
            while (temp2 != nullptr)
            {
                queueF->ui->listWidget_Input->addItem("Ordenado (0): " + temp2->data->toString());
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
    }
    if (!restaurant->kitchenRoom->kitchens[1]->InputOrders->isEmpty())
    {
        Node<Queue<Order*>*>* temp = restaurant->kitchenRoom->kitchens[1]->InputOrders->first;
        while (temp != nullptr)
        {
            Node<Order*>* temp2 = temp->data->first;
            while (temp2 != nullptr)
            {
                queueF->ui->listWidget_Input->addItem("Ordenado (1): " + temp2->data->toString());
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
    }
    if (!restaurant->kitchenRoom->kitchens[2]->InputOrders->isEmpty())
    {
        Node<Queue<Order*>*>* temp = restaurant->kitchenRoom->kitchens[2]->InputOrders->first;
        while (temp != nullptr)
        {
            Node<Order*>* temp2 = temp->data->first;
            while (temp2 != nullptr)
            {
                queueF->ui->listWidget_Input->addItem("Ordenado (2): " + temp2->data->toString());
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
    }
    if (!restaurant->kitchenRoom->OutputOrders->isEmpty())
    {
        Node<Queue<Order*>*>* temp = restaurant->kitchenRoom->OutputOrders->first;
        while (temp != nullptr)
        {
            Node<Order*>* temp2 = temp->data->first;
            while (temp2 != nullptr)
            {
                queueF->ui->listWidget_Output->addItem("Cocinado: " + temp2->data->toString());
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
    }
    if (!restaurant->kitchenRoom->dishPile->isEmpty())
    {
        Node<Order*>* temp = restaurant->kitchenRoom->dishPile->first;
        while(temp != nullptr)
        {
            queueF->ui->listWidget_Dishes->addItem("Sucio: " + temp->data->toString());
            temp = temp->next;
        }
    }
    if (!restaurant->diningRoom->bills->isEmpty())
    {
        Node<Queue<Order*>*>* temp = restaurant->diningRoom->bills->first;
        while (temp != nullptr)
        {
            Node<Order*>* temp2 = temp->data->first;
            while (temp2 != nullptr)
            {
                queueF->ui->listWidget_Bills->addItem("Cobrado: " + temp2->data->toString());
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
    }
    mutexInput0->unlock();
    mutexInput1->unlock();
    mutexInput2->unlock();
    mutexOutput->unlock();
    mutexDishes->unlock();
    mutexBills->unlock();
}

