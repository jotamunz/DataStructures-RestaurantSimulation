#include "client.h"

Client::Client(int _id, int entrySecRange[2], int mainSecRange[2], int dessertSecRange[2], int arrayPercetages[3], Menu* menu)
{
    this->id = _id;
    this->setClientEats(arrayPercetages);
    this->setClientWaitingTimes(entrySecRange, mainSecRange, dessertSecRange);
    this->setClientDishes(menu);
}

void Client::setClientWaitingTimes(int entrySecRange[2], int mainSecRange[2], int dessertSecRange[2])
{
    this->arrayClientWaitingTimes[0] = QRandomGenerator::global()->generate() % (unsigned (entrySecRange[1]) - unsigned (entrySecRange[0])) + unsigned (entrySecRange[0]);
    this->arrayClientWaitingTimes[1] = QRandomGenerator::global()->generate() % (unsigned (mainSecRange[1]) - unsigned (mainSecRange[0])) + unsigned (mainSecRange[0]);
    this->arrayClientWaitingTimes[2] = QRandomGenerator::global()->generate() % (unsigned (dessertSecRange[1]) - unsigned (dessertSecRange[0])) + unsigned (dessertSecRange[0]);
}

void Client::setClientEats(int arrayPercetages[3])
{
    this->arrayClientEats[0] = QRandomGenerator::global()->generate() % (100) <= unsigned(arrayPercetages[0]);
    this->arrayClientEats[1] = QRandomGenerator::global()->generate() % (100) <= unsigned(arrayPercetages[1]);
    this->arrayClientEats[2] = QRandomGenerator::global()->generate() % (100) <= unsigned(arrayPercetages[2]);
}

void Client::setClientDishes(Menu* menu)
{
    int randomEntry;
    int randomMain;
    int randomDessert;
    do
    {
        randomEntry = int (QRandomGenerator::global()->generate() % (unsigned (menu->dishes->size())));
    } while (menu->dishes->getPosition(randomEntry)->type != 0);
    do
    {
        randomMain = int (QRandomGenerator::global()->generate() % (unsigned (menu->dishes->size())));
    } while (menu->dishes->getPosition(randomMain)->type != 1);
    do
    {
        randomDessert = int (QRandomGenerator::global()->generate() % (unsigned (menu->dishes->size())));
    } while (menu->dishes->getPosition(randomDessert)->type != 2);
    this->arrayClientDishes[0] = menu->dishes->getPosition(randomEntry);
    this->arrayClientDishes[1] = menu->dishes->getPosition(randomMain);
    this->arrayClientDishes[2] = menu->dishes->getPosition(randomDessert);
}

QString Client::toString(){
    QString str = "Cliente #" + QVariant(this->id).toString();
    str += " [" + QVariant(this->arrayClientEats[0]).toString() + ", " + QVariant(this->arrayClientEats[1]).toString() + ", " + QVariant(this->arrayClientEats[2]).toString() + "]";
    str += " [" + QVariant(this->arrayClientWaitingTimes[0]).toString() + ", " + QVariant(this->arrayClientWaitingTimes[1]).toString() + ", " + QVariant(this->arrayClientWaitingTimes[2]).toString() + "]";
    str += " [" + this->arrayClientDishes[0]->name + ", " + this->arrayClientDishes[1]->name + ", " + this->arrayClientDishes[2]->name + "]";
    return str;
}
