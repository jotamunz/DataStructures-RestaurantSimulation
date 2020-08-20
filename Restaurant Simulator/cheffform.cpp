#include "cheffform.h"
#include "ui_cheffform.h"

cheffForm::cheffForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cheffForm)
{
    ui->setupUi(this);
    this->setStyleSheet("cheffForm{background:rgb(201,184,170);}");
    ui->listWidget->setStyleSheet("background:rgb(231,224,218);");
}

cheffForm::~cheffForm()
{
    delete ui;
}
