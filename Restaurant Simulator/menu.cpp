#include "menu.h"

//===================Ingredients========================

Ingredient::Ingredient(QString _name, int _amount)
{
    this->name = _name;
    this->amount = _amount;
}

QString Ingredient::toString()
{
    QString str = QVariant(this->amount).toString() + " " + this->name;
    return str;
}

//===================Dishes=============================

Dish::Dish(int _id, QString _name, int _type, int _prepTime, int _washTime, int _price)
{
    this->id = _id;
    this->name = _name;
    this->prepTime = _prepTime;
    this->washTime = _washTime;
    this->type = _type;
    this->price = _price;
}

QString Dish::toString()
{
    QString str = "Dish #" + QVariant(this->id).toString() + " " + this->name + "\n";
    str += "\tKitchen Type: " + QVariant(this->type).toString() + "\n";
    str += "\tPreparation Time: " + QVariant(this->prepTime).toString() + "\n";
    str += "\tWash Time: " + QVariant(this->washTime).toString() + "\n";
    str += "\tPrice: " + QVariant(this->price).toString() + "\n";
    str += "\tIngredients: \n";
    for (int i = 0; i < this->ingredients->size(); i++)
        str += "\t\t" + this->ingredients->getPosition(i)->toString() + "\n";
    return str;
}

QString Dish::toStringShort()
{
    QString str = "\tTiempo de Preparacion: " + QVariant(this->prepTime).toString() + "\n";
    str += "\tTiempo de Lavado: " + QVariant(this->washTime).toString() + "\n";
    str += "\tPrecio: " + QVariant(this->price).toString() + "\n";
    str += "\tIngredientes: \n";
    for (int i = 0; i < this->ingredients->size(); i++)
        str += "\t\t" + this->ingredients->getPosition(i)->toString() + "\n";
    return str;
}

//===================Menu==============================

Menu::Menu()
{

}

void Menu::addDish(QString name, int type, int prepTime, int washTime, int price)
{
    int id = this->dishes->size();
    Dish* dish = new Dish(id, name, type, prepTime, washTime, price);
    this->dishes->insert(dish);
}

void Menu::addIngredient(int position, QString name, int amount)
{
    Dish * dish = this->dishes->getPosition(position);
    Ingredient* ingredient = new Ingredient(name, amount);
    dish->ingredients->insert(ingredient);
}

int Menu::findDish(QString name)
{
    Node<Dish*>* temp = dishes->first;
    int count = 0;
    while (temp != nullptr)
    {
        if (temp->data->name == name)
            return count;
        count++;
        temp = temp->next;
    }
    return -1;
}

void Menu::print()
{
    for (int i = 0; i < this->dishes->size(); i++)
        qDebug().noquote() << this->dishes->getPosition(i)->toString() + "\n";
}

//===================Order=============================

Order::Order(int _table, int _clientId, Dish* _orderedDish)
{
    this->tableId = _table;
    this->clientId = _clientId;
    this->orderedDish = _orderedDish;
}

QString Order::toString()
{
    QString str = "ORDEN: ";
    str += " Mesa: " + QVariant(this->tableId).toString();
    str += " Cliente: " + QVariant(this->clientId).toString();
    str += " Plato: " + this->orderedDish->name;
    return str;
}

