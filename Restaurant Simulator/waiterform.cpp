#include "waiterform.h"
#include "ui_waiterform.h"

waiterForm::waiterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::waiterForm)
{
    ui->setupUi(this);
    this->setStyleSheet("waiterForm{background:rgb(201,184,170);}");
    ui->listWidget->setStyleSheet("background:rgb(231,224,218);");
}

waiterForm::~waiterForm()
{
    delete ui;
}
