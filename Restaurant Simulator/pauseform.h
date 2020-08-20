#ifndef PAUSEFORM_H
#define PAUSEFORM_H

#include <QWidget>
#include "controller.h"

namespace Ui {
class pauseForm;
}

class pauseForm : public QWidget
{
    Q_OBJECT

public:
    explicit pauseForm(QWidget *parent = nullptr, Controller * controller = nullptr);
    ~pauseForm();

    Controller * controller;

    //Images
    QPixmap imageWaiter = QPixmap(":/img/Images/Waiter.png");
    QPixmap imageCheff = QPixmap(":/img/Images/Cheff_Hat.png");
    QPixmap imageDoor = QPixmap(":/img/Images/Door.png");
    QPixmap imageSink = QPixmap(":/img/Images/Sink.png");
    QPixmap imageRegister = QPixmap(":/img/Images/Register.png");
    QPixmap imageClient = QPixmap(":/img/Images/Client.png");


private slots:
    void clickableButtons();

    void setImgaes();

    void on_pushBtn_K0_clicked();

    void on_pushBtn_K1_clicked();

    void on_pushBtn_K3_clicked();

    void on_pushBtn_K4_clicked();

    void on_pushBtn_K2_clicked();

    void hideButtomsWaiters();

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

    void on_pushBtn_Entry_clicked();

    void on_pushBtn_Sink_clicked();

    void on_pushBtn_Cash_clicked();

    void on_pushButton_clicked();

    void on_pushBtn_Stack_clicked();

private:
    Ui::pauseForm *ui;

};
#endif // PAUSEFORM_H
