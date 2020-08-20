#ifndef RESTAURANT_H
#define RESTAURANT_H
#include "waiter.h"
#include "kitchenroom.h"

struct Restaurant
{
public:
    Queue<int>* waiting = new Queue<int>();
    Menu* menu = new Menu();
    KitchenRoom* kitchenRoom = new KitchenRoom();
    DiningRoom* diningRoom;
    Waiter* waiters [20];

    int tableCount;
    int waiterCount;
    int orderTakingTime;
    int walkingTime;
    int entrySecRange [2];
    int mainSecRange [2];
    int dessertSecRange [2];
    int arrayPercetages [3];
    int entranceSecRange [2];
    int reservationTime;

    Restaurant(int,int);
    int unassignedWaiters();
    void assignTables();
};

#endif // RESTAURANT_H
