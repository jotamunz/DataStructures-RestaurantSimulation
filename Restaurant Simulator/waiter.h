#ifndef WAITER_H
#define WAITER_H

#include "diningroom.h"
#include "menu.h"
#include "waiterform.h"
#include "ui_waiterform.h"

struct Waiter
{
public:
    int id;
    bool active = true;
    bool assigned = false;
    bool attending = false;
    bool takingOrder = false;
    bool takingBill = false;
    bool takingDishes = false;
    bool clearingDishes = false;
    bool paused = false;
    int tableId = 0;
    int indexStart = 0;
    int indexEnd = 0;
    Queue<Order*>* newOrders = new Queue<Order*>();

    Waiter(int);
    void generateOrder(Client *, int, Table *,waiterForm*);
    QString informationString();

};

#endif // WAITER_H


