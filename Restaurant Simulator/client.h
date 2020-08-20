#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>
#include "menu.h"

struct Client
{
public:
    int id; 
    bool active = true;
    unsigned int arrayClientWaitingTimes [3];
    bool arrayClientEats [3];
    Dish* arrayClientDishes [3];
    
    Client(int, int[2], int[2], int[2], int[3], Menu*);
    void setClientWaitingTimes(int[2], int[2], int[2]);
    void setClientEats(int[3]);
    void setClientDishes(Menu*);
    QString toString();
};

#endif // CLIENT_H
