#include "menuform.h"
#include "ui_menuform.h"

menuForm::menuForm(QWidget *parent, Controller * _controller) :
    QWidget(parent),
    ui(new Ui::menuForm)
{
    ui->setupUi(this);
    this->controller = _controller;
    this->setStyleSheet("menuForm{background:rgb(201,184,170);}");
}

menuForm::~menuForm()
{
    delete ui;
}

void menuForm::on_pushButton_clicked()
{
    if (ui->lineEdit_Name->text() != "" && ui->spinBox_Type->text() != "" && ui->spinBox_PrepTime->text() != "" && ui->spinBox_WashTime->text() != "" && ui->spinBox_Price->text() != "")
    {
        controller->restaurant->menu->addDish(ui->lineEdit_Name->text(), ui->spinBox_Type->text().toInt(), ui->spinBox_PrepTime->text().toInt(), ui->spinBox_WashTime->text().toInt(), ui->spinBox_Price->text().toInt());
        qDebug() << "Plato agregado con exito";
    }
}

void menuForm::on_pushButton_2_clicked()
{
    if (ui->lineEdit_Plate->text() != "" && ui->lineEdit_Ing->text() != "" && ui->spinBox_Amount->text() != "")
    {
        int i = controller->restaurant->menu->findDish(ui->lineEdit_Plate->text());
        if (i != -1)
        {
            controller->restaurant->menu->addIngredient(i, ui->lineEdit_Ing->text(), ui->spinBox_Amount->text().toInt());
            qDebug() << "Ingrediente agregado con exito";
        }
        else
            qDebug() << "Plato no encontrado";
    }
}
