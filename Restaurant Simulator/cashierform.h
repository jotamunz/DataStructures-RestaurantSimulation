#ifndef CASHIERFORM_H
#define CASHIERFORM_H

#include <QWidget>

namespace Ui {
class cashierForm;
}

class cashierForm : public QWidget
{
    Q_OBJECT

public:
    explicit cashierForm(QWidget *parent = nullptr);
    ~cashierForm();

//private:
    Ui::cashierForm *ui;
};

#endif // CASHIERFORM_H
