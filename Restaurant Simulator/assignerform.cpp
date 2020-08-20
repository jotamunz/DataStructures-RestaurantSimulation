#include "assignerform.h"
#include "ui_assignerform.h"

assignerForm::assignerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::assignerForm)
{
    ui->setupUi(this);
    this->setStyleSheet("assignerForm{background:rgb(201,184,170);}");
    ui->listWidget->setStyleSheet("background:rgb(231,224,218);");
}

assignerForm::~assignerForm()
{
    delete ui;
}
