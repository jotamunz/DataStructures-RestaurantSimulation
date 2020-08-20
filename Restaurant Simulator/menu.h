#ifndef DISH_H
#define DISH_H

#include <qdebug.h>
#include "templates.h"

struct Ingredient
{
public:
    QString name;
    int amount;

    Ingredient(QString, int);
    QString toString();

};

struct Dish
{
public:
    int id;
    QString name;
    int type;
    int prepTime;
    int washTime;
    int price;
    SimpleList<Ingredient*>* ingredients = new SimpleList<Ingredient*>();

    Dish(int, QString, int, int, int, int);
    QString toString();
    QString toStringShort();

};

struct Menu
{
public:
    DoubleList<Dish*>* dishes = new DoubleList<Dish*>();

    Menu();
    void addDish(QString, int, int, int, int);
    void addIngredient(int, QString, int);
    int findDish(QString);
    void print();
};

struct Order
{
public:
    int tableId;
    int clientId;
    Dish* orderedDish;
    bool cooking = false;
    bool done = false;

    Order(int, int, Dish*);
    QString toString();

};

#endif // DISH_H
