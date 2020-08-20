#include "tablethread.h"

TableThread::TableThread()
{

}

void TableThread::__init__(Restaurant * _restaurant, Table * _table, assignerForm* _assignerF, tableForm * _tableF, Ui::MainWindow* _mainUI)
{
    this->restaurant = _restaurant;
    this->table = _table;
    this->assignerF = _assignerF;
    this->tableF = _tableF;
    this->mainUI = _mainUI;
    if (table->id == 0)
        this->label = mainUI->label_0;
    if (table->id == 1)
        this->label = mainUI->label_1;
    if (table->id == 2)
        this->label = mainUI->label_2;
    if (table->id == 3)
        this->label = mainUI->label_3;
    if (table->id == 4)
        this->label = mainUI->label_4;
    if (table->id == 5)
        this->label = mainUI->label_5;
    if (table->id == 6)
        this->label = mainUI->label_6;
    if (table->id == 7)
        this->label = mainUI->label_7;
    if (table->id == 8)
        this->label = mainUI->label_8;
    if (table->id == 9)
        this->label = mainUI->label_9;
    if (table->id == 10)
        this->label = mainUI->label_10;
    if (table->id == 11)
        this->label = mainUI->label_11;
    if (table->id == 12)
        this->label = mainUI->label_12;
    if (table->id == 13)
        this->label = mainUI->label_13;
    if (table->id == 14)
        this->label = mainUI->label_14;
    if (table->id == 15)
        this->label = mainUI->label_15;
    if (table->id == 16)
        this->label = mainUI->label_16;
    if (table->id == 17)
        this->label = mainUI->label_17;
    if (table->id == 18)
        this->label = mainUI->label_18;
    if (table->id == 19)
        this->label = mainUI->label_19;
}

void TableThread::run()
{
    while(this->active == true)
    {
        int reservationTime = restaurant->reservationTime;
        while (table->reserved && reservationTime != 0)
        {
            label->setNum(int (reservationTime));
            sleep(1);
            reservationTime--;
        }
        label->setNum(0);
        if (reservationTime == 0)
        {
            table->unReserveTable();
            qDebug() << "Se ha perdido la reservacion en mesa:" << table->id;
            assignerF->ui->listWidget->addItem("Se ha perdido la reservacion en mesa: " + QVariant(table->id).toString());
        }
        if(table->eating == true)
        {
            this->tableF->ui->listWidget->addItem("Mesa: " + QVariant(table->id).toString() + " comiendo por: " +QVariant(table->arrayTableWaitingTimes[table->phase]).toString() + "s");
            qDebug() << "Mesa:" << this->table->id << "Comiendo por:" << this->table->arrayTableWaitingTimes[table->phase] << "s";
            unsigned int counter = table->arrayTableWaitingTimes[table->phase];
            while (counter != 0)
            {
                label->setNum(int (counter));
                sleep(1);
                counter--;
            }
            label->setNum(0);
            table->eating = false;
            table->readyToOrder = true;
            this->tableF->ui->listWidget->addItem("Mesa: " + QVariant(table->id).toString() + " termino de comer el tiempo: " + QVariant(table->phase).toString());
            qDebug() << "Mesa:" << this->table->id << "Termino de comer el tiempo:" << table->phase;
        }
        if(table->paying == true)
        {
            qDebug() << "Mesa:" << table->id << "Lista para pagar";
            this->tableF->ui->listWidget->addItem("Mesa: " + QVariant(table->id).toString() + " paga la cuenta");
            sleep(5);
            assignerF->ui->listWidget->addItem("Mesa: " + QVariant(table->id).toString() +  " se retira");
            sleep(3);
            table->emptyTable();
        }
        else
            sleep(1);
    }
}
