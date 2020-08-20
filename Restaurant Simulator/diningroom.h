#ifndef DININGROOM_H
#define DININGROOM_H

#include "client.h"
#include <QListWidget>

struct Table
{
public:
    int id;
    bool assigned = false;
    bool reserved = false;
    unsigned int reservedAmount = 0;
    bool readyToOrder = true;
    bool eating = false;
    bool paying = false;
    bool beingAttended = false;
    int phase = 3;
    unsigned int arrayTableWaitingTimes [3] = {0,0,0};
    bool arrayTableEats [3] = {false, false, false};
    Client* clients[6];
    Queue<Order*>* dirtyDishes = new Queue<Order*>();
    Queue<Order*>* tableBill = new Queue<Order*>();

    Table(int);
    void addClient(Client*);
    void setTableWaitingTimes();
    void setTableEats();
    void changePhase();
    bool isEmpty();
    void emptyTable();
    void unReserveTable();
    QString toString();
    QString informationString();

};

struct DiningRoom
{
public:
    Table* tables[20];
    int tableCount;
    QueueStack<Queue<Order*>*>* bills = new QueueStack<Queue<Order*>*>();

    DiningRoom(int);
    int freeTableNumber();
    void addClientGroup(int, int, int, int[2], int[2], int[2], int[3], Menu*);
    int tablesUnassigned();
    void reserveTable(QListWidget*);
};

#endif // DININGROOM_H
