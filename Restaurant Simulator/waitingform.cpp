#include "waitingform.h"
#include "ui_waitingform.h"

waitingForm::waitingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::waitingForm)
{
    ui->setupUi(this);
    this->setStyleSheet("waitingForm{background:rgb(201,184,170);}");
    ui->listWidget->setStyleSheet("background:rgb(231,224,218);");
}

waitingForm::~waitingForm()
{
    delete ui;
}
