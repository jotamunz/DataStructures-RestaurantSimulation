#ifndef DISHWASHERFORM_H
#define DISHWASHERFORM_H

#include <QWidget>

namespace Ui {
class dishwasherForm;
}

class dishwasherForm : public QWidget
{
    Q_OBJECT

public:
    explicit dishwasherForm(QWidget *parent = nullptr);
    ~dishwasherForm();

//private:
    Ui::dishwasherForm *ui;
};

#endif // DISHWASHERFORM_H
