#include "diningroom.h"

//===================Tables=============================

Table::Table(int _id)
{
    this->id = _id;
    for (int i = 0; i < 6; ++i)
        this->clients[i] = nullptr;
}

void Table::addClient(Client* client)
{
    for (int i = 0; i < 6; ++i)
    {
        if (this->clients[i] == nullptr)
        {
            this->clients[i] = client;
            break;
        }
    }
}

void Table::setTableWaitingTimes()
{
    for(int i = 0; i < 3; i++) //entry, main, dessert
    {
        for(int j = 0; j < 6; j++) //clients
        {
            if (this->clients[j] != nullptr && this->clients[j]->arrayClientEats[i] == true)
            {
                if(this->clients[j]->arrayClientWaitingTimes[i] > this->arrayTableWaitingTimes[i])
                    this->arrayTableWaitingTimes[i] = this->clients[j]->arrayClientWaitingTimes[i];
            }
        }    
    }
}

void Table::setTableEats()
{
     for(int i = 0; i < 3; i++) // entry, main, dessert
     {
         for(int j = 0; j < 6; j++) //clients
         {
            if (this->clients[j] != nullptr)
            {
                if (this->clients[j]->arrayClientEats[i] == true)
                    this->arrayTableEats[i] = true;
            }
         }       
    }          
}

bool Table::isEmpty()
{
    return this->clients[0] == nullptr;
}

void Table::changePhase()
{
    this->phase += 1;
    if(this->phase == 4)
        this->phase = 0;
    if(this->phase == 0 && arrayTableEats[0] == false)
        this->phase += 1;
    if(this->phase == 1 && arrayTableEats[1] == false)
        this->phase += 1;
    if(this->phase == 2 && arrayTableEats[2] == false)
        this->phase += 1;   
}

void Table::emptyTable()
{
    this->readyToOrder = true;
    this->eating = false;
    this->phase = 3;
    this->paying = false;
    for (int i = 0; i < 3; ++i)
    {
        this->arrayTableWaitingTimes[i] = 0;
        this->arrayTableEats[i] = false;
    }
    for (int i = 0; i < 6; ++i)
        this->clients[i] = nullptr;
    this->dirtyDishes = new Queue<Order*>();
    this->tableBill = new Queue<Order*>();
}

void Table::unReserveTable()
{
    this->reserved = false;
    this->reservedAmount = 0;
}

QString Table::toString(){
    QString str = "Mesa #" + QVariant(this->id).toString();
    str += " [" + QVariant(this->arrayTableEats[0]).toString() + ", " + QVariant(this->arrayTableEats[1]).toString() + ", " + QVariant(this->arrayTableEats[2]).toString() + "]";
    str += " [" + QVariant(this->arrayTableWaitingTimes[0]).toString() + ", " + QVariant(this->arrayTableWaitingTimes[1]).toString() + ", " + QVariant(this->arrayTableWaitingTimes[2]).toString() + "]";
    return str;
}

QString Table::informationString()
{
    QString str = "Mesa #" + QVariant(this->id).toString();
    if (this->isEmpty())
    {
        str += " esta vacia";
    }
    else if (!readyToOrder && !eating && !paying)
    {
        if (phase == 0)
            str += " esta esperando la orden de entrada";
        else if (phase == 1)
            str += " esta esperando la orden de almuerzo";
        else if (phase == 2)
            str += " esta esperando al orden de postre";
        for (int i = 0; i < 6; i++)
        {
            if (clients[i] != nullptr && clients[i]->arrayClientEats[phase] == true)
                str += "\n\tCliente #" + QVariant(clients[i]->id).toString()+ " " + clients[i]->arrayClientDishes[phase]->name;
        }
    }
    else if (eating)
    {
        if (phase == 0)
            str += " esta comiendo la entrada";
        else if (phase == 1)
            str += " esta comiendo el almuerzo";
        else if (phase == 2)
            str += " esta comiendo el postre";
        for (int i = 0; i < 6; i++)
        {
            if (clients[i] != nullptr && clients[i]->arrayClientEats[phase] == true)
            {
                str += "\n\tCliente #" + QVariant(clients[i]->id).toString() + " " + clients[i]->arrayClientDishes[phase]->name;
            }
        }
    }
    else if (paying)
    {
        str += " esta pagando al cuenta";
        Node<Order*>* temp = this->tableBill->first;
        while (temp != nullptr )
        {
            str += "\n\t" + temp->data->orderedDish->name + " " + QVariant(temp->data->orderedDish->price).toString();
            temp = temp->next;
        }
    }
    else if (beingAttended)
    {
        str += " esta siendo atendida por el mesero";
        for (int i = 0; i < 6; i++)
        {
            if (clients[i] != nullptr )
                str += "\n\tCliente #" + QVariant(clients[i]->id).toString();
        }
    }
    else
    {
        str += " esta esperando atencion del mesero";
        for (int i = 0; i < 6; i++)
        {
            if (clients[i] != nullptr )
                str += "\n\tCliente #" + QVariant(clients[i]->id).toString();
        }
    }
    return str;
}

//===================DinigRoom=============================

DiningRoom::DiningRoom(int _tableCount)
{
    this->tableCount = _tableCount;
    for (int i = 0; i < 20; ++i)
    {
        if (i < _tableCount){
            this->tables[i] = new Table(i);
        }
        else
            this->tables[i] = nullptr;
    }
}

int DiningRoom::freeTableNumber()
{
    SimpleList<int> * numbers = new SimpleList<int>();
    for (int i = 0; i < 20; ++i)
    {
        if (this->tables[i] != nullptr)
        {
            if(this->tables[i]->isEmpty() && !this->tables[i]->reserved)
                numbers->insert(i);
        }
        else { break; }
    }
    if (!numbers->isEmpty())
    {
        unsigned int random = QRandomGenerator::global()->generate() % (unsigned (numbers->size()));
        int freeTable = numbers->getPosition(int (random));
        return freeTable;
    }
    return -1;
}

void DiningRoom::addClientGroup(int clientAmount, int clientCount, int tableNumber, int entrySecRange[2], int mainSecRange[2], int dessertSecRange[2], int arrayPercetages[3], Menu* menu)
{
    for (int i = 0; i < clientAmount; ++i){
        Client* client = new Client(clientCount + i, entrySecRange, mainSecRange, dessertSecRange, arrayPercetages, menu);
        this->tables[tableNumber]->addClient(client);
        qDebug().noquote() << "\t" << "\t" << client->toString();
    }
}

int DiningRoom::tablesUnassigned()
{
    int unassignedTables = 0;
    for (int i = 0; i < 20; ++i)
    {
        if (this->tables[i] != nullptr)
        {
            if(this->tables[i]->assigned == false)
                unassignedTables += 1;
        }
    }
    return unassignedTables;
}

void DiningRoom::reserveTable(QListWidget* widget)
{
    for (int i = 0; i < 20; ++i)
    {
        if (this->tables[i] != nullptr)
        {
            if(this->tables[i]->isEmpty() && !this->tables[i]->reserved)
            {
                this->tables[i]->reserved = true;
                this->tables[i]->reservedAmount = QRandomGenerator::global()->generate() % (7 - 1) + 1;
                qDebug() << "Reservacion hecha en mesa:" << i << "con codigo:" << tables[i]->reservedAmount;
                widget->addItem("Reservacion hecha en mesa: " + QVariant(i).toString() + " con codigo: " + QVariant(tables[i]->reservedAmount).toString());
                return;
            }
        }
        else { break; }
    }
    qDebug() << "No hay mesas libres para reservar";
    widget->addItem("No hay mesas disponibles para reservar");
}
