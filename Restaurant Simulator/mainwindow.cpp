#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent, int _tableCount, int _waiterCount) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setStyleSheet("QMainWindow{background:rgb(186,164,146);}");
    ui->listWidgetTable->setStyleSheet("background:rgb(224,214,206);");
    ui->listWidgetWaiter->setStyleSheet("background:rgb(224,214,206);");
    ui->listWidgetKitchen->setStyleSheet("background:rgb(224,214,206);");

    this->tableCount = _tableCount;
    this->waiterCount = _waiterCount;

    this->WaitingF = new waitingForm();
    this->AssignerF = new assignerForm();
    this->dishwasherF = new dishwasherForm();
    this->cashierF = new cashierForm();
    this->cheffF = new cheffForm();
    this->tableF = new tableForm();
    this->waiterF = new waiterForm();
    this->queueF = new queueForm();
    this->controller = new Controller(this->tableCount,this->waiterCount,this->ui,WaitingF,AssignerF,dishwasherF,cashierF,cheffF,tableF,waiterF,queueF);
    this->configF = new configForm(nullptr,this->controller);
    this->pauseF = new pauseForm(nullptr,this->controller);
    this->menuF = new menuForm(nullptr,this->controller);
    refreshT = new refreshThread(this);

    //signals and slots
    connect(refreshT,SIGNAL(refresh()),this,SLOT(windowRefresh()));
    connect(refreshT,SIGNAL(refresh()),this,SLOT(windowProgressBarUpdate()));

    //start progress bars at 0
    ui->progressBar_0->setValue(0);
    ui->progressBar_1->setValue(0);
    ui->progressBar_2->setValue(0);
    ui->progressBar_3->setValue(0);
    ui->progressBar_4->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionWaitingQueue_triggered()
{
    WaitingF->show();
}

void MainWindow::on_pushButton_clicked()
{
    refreshT->start();
    controller->startSimulation();
}

void MainWindow::on_actionAssignerDequeue_triggered()
{
    AssignerF->show();
}

void MainWindow::setImages()
{
    int w = ui->labelIMG_0->width();
    int h = ui->labelIMG_0->height();
    ui->labelIMG_0->setPixmap(imageWaiter.scaled(w,h,Qt::KeepAspectRatio));
    ui->labelIMG_13->setPixmap(imageSink.scaled(w,h,Qt::KeepAspectRatio));
    ui->labelIMG_14->setPixmap(imageRegister.scaled(w,h,Qt::KeepAspectRatio));
    w = ui->labelIMG_7->width();
    h = ui->labelIMG_7->height();
    ui->labelIMG_7->setPixmap(imageCheff.scaled(w,h,Qt::KeepAspectRatio));
    ui->labelIMG_8->setPixmap(imageCheff.scaled(w,h,Qt::KeepAspectRatio));
    ui->labelIMG_9->setPixmap(imageCheff.scaled(w,h,Qt::KeepAspectRatio));
    ui->labelIMG_10->setPixmap(imageCheff.scaled(w,h,Qt::KeepAspectRatio));
    ui->labelIMG_11->setPixmap(imageCheff.scaled(w,h,Qt::KeepAspectRatio));
    w = ui->labelIMG_1->width();
    h = ui->labelIMG_1->height();
    QLabel * clientLabels[6] = {ui->labelIMG_1,ui->labelIMG_2,ui->labelIMG_3,ui->labelIMG_4,ui->labelIMG_5,ui->labelIMG_6};
    for (int i = 0; i < 6; i++)
    {
        clientLabels[i]->setPixmap(imageClient.scaled(w,h,Qt::KeepAspectRatio));
    }
    w = ui->labelIMG_12->width();
    h = ui->labelIMG_12->height();
    ui->labelIMG_12->setPixmap(imageBell.scaled(w,h,Qt::KeepAspectRatio));
    w = ui->labelIMG_15->width();
    h = ui->labelIMG_15->height();
    ui->labelIMG_15->setPixmap(imageDoor.scaled(w,h,Qt::KeepAspectRatio));
}

void MainWindow::paintEvent(QPaintEvent *)
{
    this->setImages();
    this->hideButtomsTable();
    this->hideButtomsWaiter();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    QRectF rectangleDiningRoom(15,405,1025,480);
    QRectF rectangleKitchenRoom(15,55,1025,350);
    QRectF rectangleCashierRoom(1040,645,370,240);
    QRectF rectangleWashingRoom(1040,405,370,240);
    QRectF rectangleWaiterRoom(1040,55,370,350);
    QRectF rectangleKitchen1(80,180,250,190);
    QRectF rectangleKitchen2(380,180,250,190);
    QRectF rectangleKitchen3(680,180,250,190);
    QRectF rectangleDishwasher(1080,510,290,110);
    QRectF rectangleCashier(1080,750,290,110);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.drawRect(rectangleKitchenRoom);
    painter.drawRect(rectangleDiningRoom);
    painter.drawRect(rectangleCashierRoom);
    painter.drawRect(rectangleWashingRoom);
    painter.drawRect(rectangleWaiterRoom);
    painter.drawRect(rectangleKitchen1);
    painter.drawRect(rectangleKitchen2);
    painter.drawRect(rectangleKitchen3);
    painter.drawRect(rectangleDishwasher);
    painter.drawRect(rectangleCashier);
    int posx = 0;
    int posy = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (controller->restaurant->diningRoom->tables[(i*5)+j] != nullptr)
            {
                pen.setWidth(2);
                painter.setPen(pen);
                QRectF rectangleTable(43 + posx, 423 + posy, 85, 85);
                if (controller->restaurant->diningRoom->tables[(i*5)+j]->reserved)
                    painter.setBrush(QColor(162,138,210,200));
                else if (controller->restaurant->diningRoom->tables[(i*5)+j]->isEmpty())
                    painter.setBrush(QColor(152,251,152,200));
                else
                    painter.setBrush(QColor(255,105,97,200));
                painter.drawEllipse(rectangleTable);
            }
            posx += 180;
        }
        posx = 0;
        posy += 120;
    }
    QLabel * clientLabels[6] = {ui->labelIMG_1,ui->labelIMG_2,ui->labelIMG_3,ui->labelIMG_4,ui->labelIMG_5,ui->labelIMG_6};
    if (!controller->restaurant->waiting->isEmpty())
    {
        for (int i = 0; i < 6; i++)
            clientLabels[i]->hide();
        for (int i = 0; i < controller->restaurant->waiting->peek(); i++)
            clientLabels[i]->show();
    }
    else
    {
        for (int i = 0; i < 6; i++)
            clientLabels[i]->hide();
    }

    if (!controller->restaurant->kitchenRoom->OutputOrders->isEmpty())
    {
        ui->labelIMG_12->show();
    }
    else
        ui->labelIMG_12->hide();
}

void MainWindow::on_pushBtn_M0_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[0]->informationString());
}

void MainWindow::on_pushBtn_M1_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[1]->informationString());
}

void MainWindow::on_pushBtn_M2_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[2]->informationString());
}

void MainWindow::on_pushBtn_M3_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[3]->informationString());
}

void MainWindow::on_pushBtn_M4_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[4]->informationString());
}

void MainWindow::on_pushBtn_M5_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[5]->informationString());
}

void MainWindow::on_pushBtn_M6_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[6]->informationString());
}

void MainWindow::on_pushBtn_M7_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[7]->informationString());
}

void MainWindow::on_pushBtn_M8_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[8]->informationString());
}

void MainWindow::on_pushBtn_M9_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[9]->informationString());
}

void MainWindow::on_pushBtn_M10_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[10]->informationString());
}

void MainWindow::on_pushBtn_M11_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[11]->informationString());
}

void MainWindow::on_pushBtn_M12_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[12]->informationString());
}

void MainWindow::on_pushBtn_M13_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[13]->informationString());
}

void MainWindow::on_pushBtn_M14_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[14]->informationString());
}

void MainWindow::on_pushBtn_M15_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[15]->informationString());
}

void MainWindow::on_pushBtn_M16_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[16]->informationString());
}

void MainWindow::on_pushBtn_M17_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[17]->informationString());
}

void MainWindow::on_pushBtn_M18_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[18]->informationString());
}

void MainWindow::on_pushBtn_M19_clicked()
{
    this->ui->listWidgetTable->clear();
    this->ui->listWidgetTable->addItem(controller->restaurant->diningRoom->tables[19]->informationString());
}

void MainWindow::hideButtomsTable()
{
    for (int i = 0; i < controller->restaurant->tableCount; i++){
        if(this->controller->restaurant->diningRoom->tables[0] == nullptr){
            ui->pushBtn_M0->hide();
            ui->label_0->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[1] == nullptr){
            ui->pushBtn_M1->hide();
            ui->label_1->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[2] == nullptr){
            ui->pushBtn_M2->hide();
            ui->label_2->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[3] == nullptr){
            ui->pushBtn_M3->hide();
            ui->label_3->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[4] == nullptr){
            ui->pushBtn_M4->hide();
            ui->label_4->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[5] == nullptr){
            ui->pushBtn_M5->hide();
            ui->label_5->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[6] == nullptr){
            ui->pushBtn_M6->hide();
            ui->label_6->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[7] == nullptr){
            ui->pushBtn_M7->hide();
            ui->label_7->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[8] == nullptr){
            ui->pushBtn_M8->hide();
            ui->label_8->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[9] == nullptr){
            ui->pushBtn_M9->hide();
            ui->label_9->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[10] == nullptr){
            ui->pushBtn_M10->hide();
            ui->label_10->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[11] == nullptr){
            ui->pushBtn_M11->hide();
            ui->label_11->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[12] == nullptr){
            ui->pushBtn_M12->hide();
            ui->label_12->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[13] == nullptr){
            ui->pushBtn_M13->hide();
            ui->label_13->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[14] == nullptr){
            ui->pushBtn_M14->hide();
            ui->label_14->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[15] == nullptr){
            ui->pushBtn_M15->hide();
            ui->label_15->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[16] == nullptr){
            ui->pushBtn_M16->hide();
            ui->label_16->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[17] == nullptr){
            ui->pushBtn_M17->hide();
            ui->label_17->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[18] == nullptr){
            ui->pushBtn_M18->hide();
            ui->label_18->hide();
        }
        if(this->controller->restaurant->diningRoom->tables[19] == nullptr){
            ui->pushBtn_M19->hide();
            ui->label_19->hide();
        }
    }
}

void MainWindow::hideButtomsWaiter()
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

void MainWindow::windowRefresh()
{
    ui->centralWidget->update();
}

void MainWindow::windowProgressBarUpdate()
{
    ui->progressBar_0->setValue(this->controller->cheffThreads[0].progressBar);
    ui->progressBar_1->setValue(this->controller->cheffThreads[1].progressBar);
    ui->progressBar_2->setValue(this->controller->cheffThreads[2].progressBar);
    ui->progressBar_3->setValue(this->controller->cheffThreads[3].progressBar);
    ui->progressBar_4->setValue(this->controller->cheffThreads[4].progressBar);
}

void MainWindow::on_pushButton_2_clicked()
{
    controller->restaurant->diningRoom->reserveTable(AssignerF->ui->listWidget);
}

void MainWindow::on_pushBtn_K0_clicked()
{
    this->ui->listWidgetKitchen->clear();
    this->ui->listWidgetKitchen->addItem(this->controller->restaurant->kitchenRoom->kitchens[0]->cheffs[0]->informationString());
}

void MainWindow::on_pushBtn_K1_clicked()
{
    this->ui->listWidgetKitchen->clear();
    this->ui->listWidgetKitchen->addItem(this->controller->restaurant->kitchenRoom->kitchens[1]->cheffs[0]->informationString());
}
void MainWindow::on_pushBtn_K2_clicked()
{
    this->ui->listWidgetKitchen->clear();
    this->ui->listWidgetKitchen->addItem(this->controller->restaurant->kitchenRoom->kitchens[1]->cheffs[1]->informationString());
}
void MainWindow::on_pushBtn_K3_clicked()
{
    this->ui->listWidgetKitchen->clear();
    this->ui->listWidgetKitchen->addItem(this->controller->restaurant->kitchenRoom->kitchens[1]->cheffs[2]->informationString());
}
void MainWindow::on_pushBtn_K4_clicked()
{
    this->ui->listWidgetKitchen->clear();
    this->ui->listWidgetKitchen->addItem(this->controller->restaurant->kitchenRoom->kitchens[2]->cheffs[0]->informationString());
}

void MainWindow::on_actionSettings_triggered()
{
    configF->show();
}

void MainWindow::on_pushBtn_W0_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[0]->informationString());
}

void MainWindow::on_pushBtn_W1_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[1]->informationString());
}

void MainWindow::on_pushBtn_W2_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[2]->informationString());
}

void MainWindow::on_pushBtn_W3_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[3]->informationString());
}

void MainWindow::on_pushBtn_W4_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[4]->informationString());
}

void MainWindow::on_pushBtn_W5_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[5]->informationString());
}

void MainWindow::on_pushBtn_W6_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[6]->informationString());
}

void MainWindow::on_pushBtn_W7_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[7]->informationString());
}

void MainWindow::on_pushBtn_W8_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[8]->informationString());
}

void MainWindow::on_pushBtn_W9_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[9]->informationString());
}

void MainWindow::on_pushBtn_W10_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[10]->informationString());
}

void MainWindow::on_pushBtn_W11_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[11]->informationString());
}

void MainWindow::on_pushBtn_W12_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[12]->informationString());
}

void MainWindow::on_pushBtn_W13_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[13]->informationString());
}

void MainWindow::on_pushBtn_W14_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[14]->informationString());
}

void MainWindow::on_pushBtn_W15_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[15]->informationString());
}

void MainWindow::on_pushBtn_W16_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[16]->informationString());
}

void MainWindow::on_pushBtn_W17_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[17]->informationString());
}

void MainWindow::on_pushBtn_W18_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[18]->informationString());
}

void MainWindow::on_pushBtn_W19_clicked()
{
    this->ui->listWidgetWaiter->clear();
    this->ui->listWidgetWaiter->addItem(this->controller->restaurant->waiters[19]->informationString());
}

void MainWindow::on_actionLavado_triggered()
{
    dishwasherF->show();
}

void MainWindow::on_actionCajero_triggered()
{
    cashierF->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    controller->stopSimulation();
}

void MainWindow::on_actionPausar_triggered()
{
    pauseF->show();
}

void MainWindow::on_actionCocinas_triggered()
{
    this->cheffF->show();
}

void MainWindow::on_actionMesas_triggered()
{
    this->tableF->show();
}

void MainWindow::on_actionMeseros_triggered()
{
    this->waiterF->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
}

void MainWindow::on_actionColas_Principales_triggered()
{
    this->queueF->show();
}

void MainWindow::on_actionMenu_triggered()
{
    this->menuF->show();
}
