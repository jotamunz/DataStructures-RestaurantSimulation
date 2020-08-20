#ifndef KITCHENROOM_H
#define KITCHENROOM_H

#include "menu.h"

struct Cheff
{
public:
    int id;
    int kitchenType;
    bool active = true;
    bool cooking = false;
    bool paused = false;
    Order * order = nullptr;

    Cheff(int, int);
    QString getId();
    QString getKitchenType();
    QString informationString();
};

struct Kitchen
{
public:
    int id;
    bool active = true;
    Cheff* cheffs[3];
    Queue<Queue<Order*>*>* InputOrders = new Queue<Queue<Order*>*>();

    Kitchen(int);
};

struct KitchenRoom
{
public:
    Kitchen* kitchens[3];
    SimpleList<Queue<Order*>*>* OutputOrders = new SimpleList<Queue<Order*>*>();
    Queue<Order*>* dishPile = new Queue<Order*>();

    KitchenRoom();
};

#endif // KITCHENROOM_H
