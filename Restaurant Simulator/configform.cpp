#include "configform.h"
#include "ui_configform.h"

configForm::configForm(QWidget *parent, Controller * _controller) :
    QWidget(parent),
    ui(new Ui::configForm)
{
    ui->setupUi(this);
    this->controller = _controller;
    this->setStyleSheet("configForm{background:rgb(201,184,170);}");
}

configForm::~configForm()
{
    delete ui;
}

void configForm::on_pushButton_clicked()
{
    if (this->ui->spinBox_EntranceStart->text() != "")
        controller->restaurant->entranceSecRange[0] = this->ui->spinBox_EntranceStart->text().toInt();
    if (this->ui->spinBox_EntranceEnd->text() != "")
        controller->restaurant->entranceSecRange[1] = this->ui->spinBox_EntranceEnd->text().toInt();
    if (this->ui->spinBox_OrderTakingTime->text() != "")
        controller->restaurant->orderTakingTime = this->ui->spinBox_OrderTakingTime->text().toInt();
    if (this->ui->spinBox_WalkingTime->text() != "")
        controller->restaurant->walkingTime = this->ui->spinBox_WalkingTime->text().toInt();
    if (this->ui->spinBox_ReservationTime->text() != "")
        controller->restaurant->reservationTime = this->ui->spinBox_ReservationTime->text().toInt();
    if (this->ui->spinBox_EntryStart->text() != "")
        controller->restaurant->entrySecRange[0] = this->ui->spinBox_EntryStart->text().toInt();
    if (this->ui->spinBox_EntryEnd->text() != "")
        controller->restaurant->entrySecRange[1] = this->ui->spinBox_EntryEnd->text().toInt();
    if (this->ui->spinBox_MainStart->text() != "")
        controller->restaurant->mainSecRange[0] = this->ui->spinBox_MainStart->text().toInt();
    if (this->ui->spinBox_MainEnd->text() != "")
        controller->restaurant->mainSecRange[1] = this->ui->spinBox_MainEnd->text().toInt();
    if (this->ui->spinBox_DessertStart->text() != "")
        controller->restaurant->dessertSecRange[0] = this->ui->spinBox_DessertStart->text().toInt();
    if (this->ui->spinBox_DessertEnd->text() != "")
        controller->restaurant->dessertSecRange[1] = this->ui->spinBox_DessertEnd->text().toInt();
    if (this->ui->spinBox_EntryProb->text() != "")
        controller->restaurant->arrayPercetages[0] = this->ui->spinBox_EntryProb->text().toInt();
    if (this->ui->spinBox_MainProb->text() != "")
        controller->restaurant->arrayPercetages[1] = this->ui->spinBox_MainProb->text().toInt();
    if (this->ui->spinBox_DessertProb->text() != "")
        controller->restaurant->arrayPercetages[2] = this->ui->spinBox_DessertProb->text().toInt();
    this->hide();
}
