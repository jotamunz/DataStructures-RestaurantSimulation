#include "kitchenroom.h"

//===================Cheff=============================

Cheff::Cheff(int _kitchenType, int _id)
{
    this->kitchenType = _kitchenType;
    this->id = _id;
}

QString Cheff::getId()
{
    QString str = QVariant(this->kitchenType).toString();
    str += "(" + QVariant(this->id).toString() + ")";
    return str;
}

QString Cheff::getKitchenType()
{
    if(this->kitchenType == 0)
        return " Entradas";
    else if(this->kitchenType == 1)
        return " Platos Fuertes";
    else
        return " Postres";
}


QString Cheff::informationString()
{
    QString str = "Chef #" + QVariant(this->id).toString() + this->getKitchenType() + "\n";
    if (paused)
        str += "esta pausado";
    else if(cooking)
    {
        str += "esta cocinando la orden: ";
        str += "\n" + this->order->toString();
        str += "\n" + this->order->orderedDish->toStringShort();
    }
    else
        str += "esta esperando una orden para cocinar";
    return str;
}


//===================Kitchen===========================

Kitchen::Kitchen(int _id)
{
    this->id = _id;
    if (_id == 0 || _id == 2)    //cocinas entry y dessert
    {
        for (int i = 0; i < 3; ++i)
        {
            if (i < 1){
                this->cheffs[i] = new Cheff(_id, i);
            }
            else
                this->cheffs[i] = nullptr;
        }
    }
    else if (_id == 1)           //cocina main
    {
        for (int i = 0; i < 3; ++i)
                this->cheffs[i] = new Cheff(_id, i);
    }
}

//===================Kitchenroom=========================

KitchenRoom::KitchenRoom()
{
    for (int i = 0; i < 3; ++i)
    {
        this->kitchens[i] = new Kitchen(i);
    }
}
