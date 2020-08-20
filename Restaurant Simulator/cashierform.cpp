#include "cashierform.h"
#include "ui_cashierform.h"

cashierForm::cashierForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cashierForm)
{
    ui->setupUi(this);
    this->setStyleSheet("cashierForm{background:rgb(201,184,170);}");
    ui->listWidget->setStyleSheet("background:rgb(231,224,218);");
}

cashierForm::~cashierForm()
{
    delete ui;
}
