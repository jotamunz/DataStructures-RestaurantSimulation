#include "queueform.h"
#include "ui_queueform.h"

queueForm::queueForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::queueForm)
{
    ui->setupUi(this);
    this->setStyleSheet("queueForm{background:rgb(201,184,170);}");
    ui->listWidget_Input->setStyleSheet("background:rgb(231,224,218);");
    ui->listWidget_Output->setStyleSheet("background:rgb(231,224,218);");
    ui->listWidget_Dishes->setStyleSheet("background:rgb(231,224,218);");
    ui->listWidget_Bills->setStyleSheet("background:rgb(231,224,218);");
}

queueForm::~queueForm()
{
    delete ui;
}
