#include "controller.h"

Controller::Controller(int _tableCount, int _waiterCount, Ui::MainWindow* _mainUI, waitingForm * _waitingF, assignerForm * _assignerF, dishwasherForm * _dishwasherF, cashierForm * _cashierF, cheffForm * _cheffF, tableForm * _tableF, waiterForm * _waiterF, queueForm * _queueF)
{
    this->tableCount = _tableCount;
    this->waiterCount = _waiterCount;
    this->restaurant = new Restaurant(tableCount, waiterCount);
    this->assignerF = _assignerF;
    this->waitingF = _waitingF;
    this->dishwasherF = _dishwasherF;
    this->cashierF = _cashierF;
    this->cheffF = _cheffF;
    this->tableF = _tableF;
    this->waiterF = _waiterF;
    this->queueF = _queueF;
    this->mainUI = _mainUI;
}

void Controller::startSimulation()
{
    this->restaurant->assignTables();
    this->entry.__init__(restaurant, mutexEntry, waitingF);
    this->assigner.__init__(restaurant, mutexEntry, assignerF, tableF);
    this->dishWasher.__init__(restaurant, mutexDishes, dishwasherF, mainUI);
    this->cashier.__init__(restaurant, mutexBills, cashierF, mainUI);

    for (int i = 0; i < restaurant->tableCount; i++){
        this->tableThreads[i].__init__(restaurant, restaurant->diningRoom->tables[i], assignerF, tableF, mainUI);
        this->tableThreads[i].start();
    }

    for (int i = 0; i < restaurant->waiterCount; i++){
        this->waiterThreads[i].__init__(restaurant, restaurant->waiters[i], mutexOutput, mutexDishes, mutexInput0, mutexInput1, mutexInput2, mutexBills, waiterF, queueF);
        this->waiterThreads[i].start();
    }

    for (int i = 0; i < 5; i++)
    {
        if (i == 0)
        {
            this->cheffThreads[i].__init__(restaurant, restaurant->kitchenRoom->kitchens[0]->cheffs[0], mutexInput0, mutexOutput, cheffF, mainUI);
            this->cheffThreads[i].start();
        }
        if (i == 1 || i == 2 || i == 3)
        {
            this->cheffThreads[i].__init__(restaurant, restaurant->kitchenRoom->kitchens[1]->cheffs[i-1], mutexInput1, mutexOutput, cheffF, mainUI);
            this->cheffThreads[i].start();
        }
        if (i == 4){
            this->cheffThreads[i].__init__(restaurant, restaurant->kitchenRoom->kitchens[2]->cheffs[0], mutexInput2, mutexOutput, cheffF, mainUI);
            this->cheffThreads[i].start();
        }
    }

    this->entry.start();
    this->assigner.start();
    this->dishWasher.start();
    this->cashier.start();
}

void Controller::stopSimulation()
{
    this->entry.active = false;
    this->assigner.active = false;
    this->dishWasher.active = false;
    this->cashier.active = false;

    for (int i = 0; i < restaurant->tableCount; i++)
        this->tableThreads[i].active = false;

    for (int i = 0; i < restaurant->waiterCount; i++)
        this->waiterThreads[i].active = false;

    for (int i = 0; i < 5; i++)
        this->cheffThreads[i].active = false;
}
