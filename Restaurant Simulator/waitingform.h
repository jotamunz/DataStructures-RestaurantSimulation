#ifndef WAITINGFORM_H
#define WAITINGFORM_H

#include <QWidget>

namespace Ui {
class waitingForm;
}

class waitingForm : public QWidget
{
    Q_OBJECT

public:
    explicit waitingForm(QWidget *parent = nullptr);
    ~waitingForm();

//private:
    Ui::waitingForm *ui;
};

#endif // WAITINGFORM_H
