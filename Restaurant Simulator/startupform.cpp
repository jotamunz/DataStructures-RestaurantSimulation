#include "startupform.h"
#include "ui_startupform.h"
#include "mainwindow.h"

StartupForm::StartupForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartupForm)
{
    ui->setupUi(this);
    this->setStyleSheet("StartupForm{background:rgb(201,184,170);}");
}

StartupForm::~StartupForm()
{
    delete ui;
}

void StartupForm::on_pushButton_Conf_clicked()
{
    this->tableCount = this->ui->spinBox_0->text().toInt();
    this->waiterCount = this->ui->spinBox_1->text().toInt();
    if (this->waiterCount <= this->tableCount)
    {
        MainWindow * mainWindow = new MainWindow(nullptr,tableCount,waiterCount);
        mainWindow->show();
        this->hide();
    }
}
