#ifndef CONFIGFORM_H
#define CONFIGFORM_H

#include <QWidget>
#include "controller.h"

namespace Ui {
class configForm;
}

class configForm : public QWidget
{
    Q_OBJECT

public:
    explicit configForm(QWidget *parent = nullptr, Controller * controller = nullptr);
    ~configForm();

    Controller * controller;

private slots:
    void on_pushButton_clicked();

private:
    Ui::configForm *ui;
};

#endif // CONFIGFORM_H
