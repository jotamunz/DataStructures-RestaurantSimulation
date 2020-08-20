#include "dishwasherform.h"
#include "ui_dishwasherform.h"

dishwasherForm::dishwasherForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dishwasherForm)
{
    ui->setupUi(this);
    this->setStyleSheet("dishwasherForm{background:rgb(201,184,170);}");
    ui->listWidget->setStyleSheet("background:rgb(231,224,218);");
}

dishwasherForm::~dishwasherForm()
{
    delete ui;
}
