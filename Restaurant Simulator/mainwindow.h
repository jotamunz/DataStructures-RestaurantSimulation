#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"
#include "ui_mainwindow.h"
#include "refreshthread.h"
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QPalette>
#include "waitingform.h"
#include "ui_waitingform.h"
#include "assignerform.h"
#include "ui_assignerform.h"
#include "configform.h"
#include "ui_configform.h"
#include "dishwasherform.h"
#include "ui_dishwasherform.h"
#include "cashierform.h"
#include "ui_cashierform.h"
#include "pauseform.h"
#include "ui_pauseform.h"
#include "cheffform.h"
#include "ui_cheffform.h"
#include "tableform.h"
#include "ui_tableform.h"
#include "waiterform.h"
#include "ui_waiterform.h"
#include "queueform.h"
#include "ui_queueform.h"
#include "menuform.h"
#include "ui_menuform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, int tableCount = 10, int waiterCount = 5);
    ~MainWindow();

    //from start window
    int tableCount;
    int waiterCount;

    waitingForm  * WaitingF;
    assignerForm * AssignerF;
    Controller * controller;
    refreshThread * refreshT;
    configForm * configF;
    dishwasherForm * dishwasherF;
    cashierForm * cashierF;
    pauseForm * pauseF;
    menuForm * menuF;
    cheffForm * cheffF;
    tableForm * tableF;
    waiterForm * waiterF;
    queueForm * queueF;

    QPixmap imageWaiter = QPixmap(":/img/Images/Waiter.png");
    QPixmap imageCheff = QPixmap(":/img/Images/Cheff_Hat.png");
    QPixmap imageClient = QPixmap(":/img/Images/Client.png");
    QPixmap imageBell = QPixmap(":/img/Images/Bell.png");
    QPixmap imageSink = QPixmap(":/img/Images/Sink.png");
    QPixmap imageRegister = QPixmap(":/img/Images/Register.png");
    QPixmap imageDoor = QPixmap(":/img/Images/Door.png");

    virtual void paintEvent(QPaintEvent*);
public slots:
    void on_actionWaitingQueue_triggered();
    void on_pushButton_clicked();
    void on_actionAssignerDequeue_triggered();
    void on_pushBtn_M0_clicked();
    void on_pushBtn_M1_clicked();
    void on_pushBtn_M2_clicked();
    void on_pushBtn_M3_clicked();
    void on_pushBtn_M4_clicked();
    void hideButtomsTable();
    void hideButtomsWaiter();
    void setImages();
    void on_pushBtn_M5_clicked();
    void on_pushBtn_M6_clicked();
    void on_pushBtn_M7_clicked();
    void on_pushBtn_M8_clicked();
    void on_pushBtn_M9_clicked();
    void on_pushBtn_M10_clicked();
    void on_pushBtn_M11_clicked();
    void on_pushBtn_M12_clicked();
    void on_pushBtn_M13_clicked();
    void on_pushBtn_M14_clicked();
    void on_pushBtn_M15_clicked();
    void on_pushBtn_M16_clicked();
    void on_pushBtn_M17_clicked();
    void on_pushBtn_M18_clicked();
    void on_pushBtn_M19_clicked();
    void on_pushBtn_K0_clicked();
    void on_pushBtn_K1_clicked();
    void on_pushBtn_K2_clicked();
    void on_pushBtn_K3_clicked();
    void on_pushBtn_K4_clicked();
    void on_pushBtn_W0_clicked();
    void on_pushBtn_W1_clicked();
    void on_pushBtn_W2_clicked();
    void on_pushBtn_W3_clicked();
    void on_pushBtn_W4_clicked();
    void on_pushBtn_W5_clicked();
    void on_pushBtn_W6_clicked();
    void on_pushBtn_W7_clicked();
    void on_pushBtn_W8_clicked();
    void on_pushBtn_W9_clicked();
    void on_pushBtn_W10_clicked();
    void on_pushBtn_W11_clicked();
    void on_pushBtn_W12_clicked();
    void on_pushBtn_W13_clicked();
    void on_pushBtn_W14_clicked();
    void on_pushBtn_W15_clicked();
    void on_pushBtn_W16_clicked();
    void on_pushBtn_W17_clicked();
    void on_pushBtn_W18_clicked();
    void on_pushBtn_W19_clicked();
    void windowRefresh();
    void windowProgressBarUpdate();
    void on_pushButton_2_clicked();
    void on_actionSettings_triggered();
    void on_actionLavado_triggered();
    void on_actionCajero_triggered();
    void on_pushButton_3_clicked();
    void on_actionPausar_triggered();
    void on_actionCocinas_triggered();
    void on_actionMesas_triggered();
    void on_actionMeseros_triggered();
    void on_pushButton_5_clicked();
    void on_actionColas_Principales_triggered();

private slots:
    void on_actionMenu_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
