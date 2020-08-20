#include "tableform.h"
#include "ui_tableform.h"

tableForm::tableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tableForm)
{
    ui->setupUi(this);
    this->setStyleSheet("tableForm{background:rgb(201,184,170);}");
    ui->listWidget->setStyleSheet("background:rgb(231,224,218);");
}

tableForm::~tableForm()
{
    delete ui;
}
