#ifndef QUEUEFORM_H
#define QUEUEFORM_H

#include <QWidget>

namespace Ui {
class queueForm;
}

class queueForm : public QWidget
{
    Q_OBJECT

public:
    explicit queueForm(QWidget *parent = nullptr);
    ~queueForm();

//private:
    Ui::queueForm *ui;
};

#endif // QUEUEFORM_H
