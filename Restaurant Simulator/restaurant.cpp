#include "restaurant.h"

Restaurant::Restaurant(int _tableCount, int _waiterCount)
{
    //restaurant information
    this->tableCount = _tableCount;
    this->waiterCount = _waiterCount;
    //entrance information
    this->entranceSecRange [0] = 10;
    this->entranceSecRange [1] = 15;
    //waiter information
    this->orderTakingTime = 3;
    this->walkingTime = 3;
    //reservations information
    this->reservationTime = 50;
    //client information
    this->entrySecRange [0] = 20;
    this->entrySecRange [1] = 30;
    this->mainSecRange [0] = 30;
    this->mainSecRange [1] = 60;
    this->dessertSecRange [0] = 10;
    this->dessertSecRange [1] = 20;
    this->arrayPercetages [0] = 40;
    this->arrayPercetages [1] = 90;
    this->arrayPercetages [2] = 20;
    //menu
    this->menu->addDish("Ensalada", 0, 20, 5, 2000);
    this->menu->addDish("Sopa", 0, 20, 5, 2000);
    this->menu->addDish("Focaccia", 0, 25, 5, 2000);
    this->menu->addDish("Pizza", 1, 50, 15, 3000);
    this->menu->addDish("Pasta", 1, 40, 15, 3000);
    this->menu->addDish("Ravioli", 1, 60, 15, 3000);
    this->menu->addDish("Lasagna", 1, 50, 15, 3000);
    this->menu->addDish("Helado", 2, 10, 10, 1000);
    this->menu->addDish("Queque", 2, 20, 10, 1000);
    this->menu->addDish("Brownie", 2, 30, 10, 1000);
    this->menu->addIngredient(0, "Lechuga", 8);
    this->menu->addIngredient(0, "Tomate", 2);
    this->menu->addIngredient(1, "Agua", 10);
    this->menu->addIngredient(2, "Albahaca", 8);
    this->menu->addIngredient(2, "Tomate", 2);
    this->menu->addIngredient(3, "Queso", 5);
    this->menu->addIngredient(3, "Salsa", 5);
    this->menu->addIngredient(3, "Pepperoni", 1);
    this->menu->addIngredient(4, "Fideos", 5);
    this->menu->addIngredient(4, "Salsa", 5);
    this->menu->addIngredient(4, "Mantequilla", 1);
    this->menu->addIngredient(5, "Masa", 5);
    this->menu->addIngredient(5, "Salsa", 5);
    this->menu->addIngredient(5, "Carne", 1);
    this->menu->addIngredient(6, "Masa", 5);
    this->menu->addIngredient(6, "Salsa", 5);
    this->menu->addIngredient(6, "Carne", 1);
    this->menu->addIngredient(7, "Vainilla", 1);
    this->menu->addIngredient(8, "Chocolate", 2);
    this->menu->addIngredient(9, "Chocolate", 2);
    this->menu->print();

    this->diningRoom = new DiningRoom(this->tableCount);
    for (int i = 0; i < 20; ++i)
    {
        if (i < this->waiterCount){
            this->waiters[i] = new Waiter(i);
        }
        else
            this->waiters[i] = nullptr;
    }
}

int Restaurant::unassignedWaiters()
{
    int unassignedWaitersAmount = 0;
    for(unsigned int i = 0; i < sizeof(this->waiters)/sizeof(this->waiters[0]); i++)
    {
        if(waiters[i] != nullptr && waiters[i]->assigned == false)
            unassignedWaitersAmount += 1;
    }
    return unassignedWaitersAmount;
}

void Restaurant::assignTables()
{
    for(unsigned int i = 0; i < sizeof(this->waiters)/sizeof(this->waiters[0]); i++) // waiters
    {
        if(this->waiters[i] != nullptr)
        {
            int tablesToAssignAmount = this->diningRoom->tablesUnassigned()/this->unassignedWaiters();
            this->waiters[i]->assigned = true;
            for(int j = 0; tablesToAssignAmount != 0; j++) // tables
            {
                if(this->diningRoom->tables[j]->assigned == false)
                {
                    if(waiters[i]->indexStart == 0 && this->diningRoom->tables[0]->assigned == true && i != 0)
                        waiters[i]->indexStart = j;
                    waiters[i]->indexEnd = j;
                    tablesToAssignAmount -= 1;
                    this->diningRoom->tables[j]->assigned = true;
                }
            }
            qDebug().noquote() << "Waiter:" << i << "serves from:" << waiters[i]->indexStart << "to" << waiters[i]->indexEnd;
        }
    }
    qDebug().noquote() << "\n" << "Simulation Start" << "\n";
}
