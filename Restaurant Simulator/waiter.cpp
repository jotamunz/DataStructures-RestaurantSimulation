#include "waiter.h"

Waiter::Waiter(int _id)
{
    this->id = _id;
}

void Waiter::generateOrder(Client *client, int phase, Table *table, waiterForm * waiterF)
{
    if(phase < 3 && client->arrayClientEats[phase])
    {
        Order* order = new Order(table->id, client->id, client->arrayClientDishes[phase]);
        this->newOrders->queue(order);
        table->tableBill->queue(order);
        waiterF->ui->listWidget->addItem("           " + order->toString());
        qDebug().noquote() << "\t" << order->toString();
    }
}

QString Waiter::informationString()
{
    QString str = "Mesero #" + QVariant(this->id).toString();
    if (this->paused)
        str += " esta pausado";
    else if (this->takingOrder)
    {
        str += " esta tomando la orden de la mesa #" + QVariant(this->tableId).toString();
        Node<Order*>* temp = this->newOrders->first;
        while (temp != nullptr)
        {
            str += "\n" + temp->data->toString();
            temp = temp->next;
        }
    }
    else if (this->takingBill)
    {
        str += " esta llevando la cuenta de la mesa #" + QVariant(this->tableId).toString();
    }
    else if (this->takingDishes)
    {
        str += " esta llevando los platos a la mesa #" + QVariant(this->tableId).toString();
        Node<Order*>* temp = this->newOrders->first;
        while (temp != nullptr)
        {
            str += "\n" + temp->data->toString();
            temp = temp->next;
        }
    }
    else if (this->clearingDishes)
    {
        str += " esta recogiendo los platos sucios de la mesa #" + QVariant(this->tableId).toString();
    }
    else if (this->attending)
    {
        str += " esta atendiendo a la mesa #" + QVariant(this->tableId).toString();
    }
    else
    {
        str += " esta desocupado";
    }
    return str;
}
