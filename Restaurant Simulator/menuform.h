#ifndef MENUFORM_H
#define MENUFORM_H

#include <QWidget>
#include "controller.h"

namespace Ui {
class menuForm;
}

class menuForm : public QWidget
{
    Q_OBJECT

public:
    explicit menuForm(QWidget *parent = nullptr, Controller * controller = nullptr);
    ~menuForm();

    Controller * controller;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::menuForm *ui;
};

#endif // MENUFORM_H
