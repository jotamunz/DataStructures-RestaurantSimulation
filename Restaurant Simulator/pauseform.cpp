#include "pauseform.h"
#include "ui_pauseform.h"

pauseForm::pauseForm(QWidget *parent, Controller * _controller) :
    QWidget(parent),
    ui(new Ui::pauseForm)
{
    ui->setupUi(this);
    this->controller = _controller;
    this->hideButtomsWaiters();
    this->setStyleSheet("pauseForm{background:rgb(201,184,170);}");
    clickableButtons();
    setImgaes();
}

pauseForm::~pauseForm()
{
    delete ui;
}

void pauseForm::clickableButtons()
{
    ui->pushBtn_K0->setCheckable(true);
    ui->pushBtn_K1->setCheckable(true);
    ui->pushBtn_K2->setCheckable(true);
    ui->pushBtn_K3->setCheckable(true);
    ui->pushBtn_K4->setCheckable(true);
    ui->pushBtn_W0->setCheckable(true);
    ui->pushBtn_W1->setCheckable(true);
    ui->pushBtn_W2->setCheckable(true);
    ui->pushBtn_W3->setCheckable(true);
    ui->pushBtn_W4->setCheckable(true);
    ui->pushBtn_W5->setCheckable(true);
    ui->pushBtn_W6->setCheckable(true);
    ui->pushBtn_W7->setCheckable(true);
    ui->pushBtn_W8->setCheckable(true);
    ui->pushBtn_W9->setCheckable(true);
    ui->pushBtn_W10->setCheckable(true);
    ui->pushBtn_W11->setCheckable(true);
    ui->pushBtn_W12->setCheckable(true);
    ui->pushBtn_W13->setCheckable(true);
    ui->pushBtn_W14->setCheckable(true);
    ui->pushBtn_W15->setCheckable(true);
    ui->pushBtn_W16->setCheckable(true);
    ui->pushBtn_W17->setCheckable(true);
    ui->pushBtn_W18->setCheckable(true);
    ui->pushBtn_W19->setCheckable(true);
    ui->pushBtn_Sink->setCheckable(true);
    ui->pushBtn_Entry->setCheckable(true);
    ui->pushBtn_Cash->setCheckable(true);
    ui->pushButton->setCheckable(true);
    ui->pushBtn_Stack->setCheckable(true);
}

void pauseForm::setImgaes()
{
    int w = ui->labelIMG_7->width();
    int h = ui->labelIMG_7->height();
    ui->labelIMG_7->setPixmap(imageCheff.scaled(w,h,Qt::KeepAspectRatio));
    ui->labelIMG_8->setPixmap(imageCheff.scaled(w,h,Qt::KeepAspectRatio));
    ui->labelIMG_9->setPixmap(imageCheff.scaled(w,h,Qt::KeepAspectRatio));
    ui->labelIMG_10->setPixmap(imageCheff.scaled(w,h,Qt::KeepAspectRatio));
    ui->labelIMG_11->setPixmap(imageCheff.scaled(w,h,Qt::KeepAspectRatio));
    w = ui->labelIMG_15->width();
    h = ui->labelIMG_15->height();
    ui->labelIMG_15->setPixmap(imageDoor.scaled(w,h,Qt::KeepAspectRatio));
    w = ui->labelIMG_0->width();
    h = ui->labelIMG_0->height();
    ui->labelIMG_0->setPixmap(imageWaiter.scaled(w,h,Qt::KeepAspectRatio));
    w = ui->labelIMG_13->width();
    h = ui->labelIMG_13->height();
    ui->labelIMG_13->setPixmap(imageSink.scaled(w,h,Qt::KeepAspectRatio));
    w = ui->labelIMG_14->width();
    h = ui->labelIMG_14->height();
    ui->labelIMG_14->setPixmap(imageRegister.scaled(w,h,Qt::KeepAspectRatio));
    w = ui->labelIMG_6->width();
    h = ui->labelIMG_6->height();
    ui->labelIMG_6->setPixmap(imageClient.scaled(w,h,Qt::KeepAspectRatio));
}

void pauseForm::on_pushBtn_K0_clicked()
{
    this->controller->cheffThreads[0].pause();
}

void pauseForm::on_pushBtn_K1_clicked()
{
    this->controller->cheffThreads[1].pause();
}
void pauseForm::on_pushBtn_K2_clicked()
{
   this->controller->cheffThreads[2].pause();
}

void pauseForm::on_pushBtn_K3_clicked()
{
    this->controller->cheffThreads[3].pause();
}

void pauseForm::on_pushBtn_K4_clicked()
{
    this->controller->cheffThreads[4].pause();
}

void pauseForm::hideButtomsWaiters()
{
    for (int i = 0; i < controller->restaurant->waiterCount; i++){
        if(this->controller->restaurant->waiters[0] == nullptr){
            ui->pushBtn_W0->hide();
        }
        if(this->controller->restaurant->waiters[1] == nullptr){
            ui->pushBtn_W1->hide();
        }
        if(this->controller->restaurant->waiters[2] == nullptr){
            ui->pushBtn_W2->hide();
        }
        if(this->controller->restaurant->waiters[3] == nullptr){
            ui->pushBtn_W3->hide();
        }
        if(this->controller->restaurant->waiters[4] == nullptr){
            ui->pushBtn_W4->hide();
        }
        if(this->controller->restaurant->waiters[5] == nullptr){
            ui->pushBtn_W5->hide();
        }
        if(this->controller->restaurant->waiters[6] == nullptr){
            ui->pushBtn_W6->hide();
        }
        if(this->controller->restaurant->waiters[7] == nullptr){
            ui->pushBtn_W7->hide();
        }
        if(this->controller->restaurant->waiters[8] == nullptr){
            ui->pushBtn_W8->hide();
        }
        if(this->controller->restaurant->waiters[9] == nullptr){
            ui->pushBtn_W9->hide();
        }
        if(this->controller->restaurant->waiters[10] == nullptr){
            ui->pushBtn_W10->hide();
        }
        if(this->controller->restaurant->waiters[11] == nullptr){
            ui->pushBtn_W11->hide();
        }
        if(this->controller->restaurant->waiters[12] == nullptr){
            ui->pushBtn_W12->hide();
        }
        if(this->controller->restaurant->waiters[13] == nullptr){
            ui->pushBtn_W13->hide();
        }
        if(this->controller->restaurant->waiters[14] == nullptr){
            ui->pushBtn_W14->hide();
        }
        if(this->controller->restaurant->waiters[15] == nullptr){
            ui->pushBtn_W15->hide();
        }
        if(this->controller->restaurant->waiters[16] == nullptr){
            ui->pushBtn_W16->hide();
        }
        if(this->controller->restaurant->waiters[17] == nullptr){
            ui->pushBtn_W17->hide();
        }
        if(this->controller->restaurant->waiters[18] == nullptr){
            ui->pushBtn_W18->hide();
        }
        if(this->controller->restaurant->waiters[19] == nullptr){
            ui->pushBtn_W19->hide();
        }
    }
}



void pauseForm::on_pushBtn_W0_clicked()
{
    this->controller->waiterThreads[0].pause();
}
void pauseForm::on_pushBtn_W1_clicked()
{
    this->controller->waiterThreads[1].pause();
}
void pauseForm::on_pushBtn_W2_clicked()
{
    this->controller->waiterThreads[2].pause();
}
void pauseForm::on_pushBtn_W3_clicked()
{
    this->controller->waiterThreads[3].pause();
}
void pauseForm::on_pushBtn_W4_clicked()
{
    this->controller->waiterThreads[4].pause();
}
void pauseForm::on_pushBtn_W5_clicked()
{
    this->controller->waiterThreads[5].pause();
}
void pauseForm::on_pushBtn_W6_clicked()
{
    this->controller->waiterThreads[6].pause();
}
void pauseForm::on_pushBtn_W7_clicked()
{
    this->controller->waiterThreads[7].pause();
}
void pauseForm::on_pushBtn_W8_clicked()
{
    this->controller->waiterThreads[8].pause();
}
void pauseForm::on_pushBtn_W9_clicked()
{
    this->controller->waiterThreads[9].pause();
}
void pauseForm::on_pushBtn_W10_clicked()
{
    this->controller->waiterThreads[10].pause();
}
void pauseForm::on_pushBtn_W11_clicked()
{
    this->controller->waiterThreads[11].pause();
}
void pauseForm::on_pushBtn_W12_clicked()
{
    this->controller->waiterThreads[12].pause();
}
void pauseForm::on_pushBtn_W13_clicked()
{
    this->controller->waiterThreads[13].pause();
}
void pauseForm::on_pushBtn_W14_clicked()
{
    this->controller->waiterThreads[14].pause();
}
void pauseForm::on_pushBtn_W15_clicked()
{
    this->controller->waiterThreads[15].pause();
}
void pauseForm::on_pushBtn_W16_clicked()
{
    this->controller->waiterThreads[16].pause();
}
void pauseForm::on_pushBtn_W17_clicked()
{
    this->controller->waiterThreads[17].pause();
}
void pauseForm::on_pushBtn_W18_clicked()
{
    this->controller->waiterThreads[18].pause();
}
void pauseForm::on_pushBtn_W19_clicked()
{
    this->controller->waiterThreads[19].pause();
}

void pauseForm::on_pushBtn_Entry_clicked()
{
    this->controller->entry.pause();
}

void pauseForm::on_pushBtn_Sink_clicked()
{
    this->controller->dishWasher.pause();
}

void pauseForm::on_pushBtn_Cash_clicked()
{
    this->controller->cashier.pause();
}

void pauseForm::on_pushButton_clicked()
{
    this->controller->assigner.pause();
}

void pauseForm::on_pushBtn_Stack_clicked()
{
    this->controller->restaurant->diningRoom->bills->switchMode();
}
