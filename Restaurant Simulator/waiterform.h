#ifndef WAITERFORM_H
#define WAITERFORM_H

#include <QWidget>

namespace Ui {
class waiterForm;
}

class waiterForm : public QWidget
{
    Q_OBJECT

public:
    explicit waiterForm(QWidget *parent = nullptr);
    ~waiterForm();

//private:
    Ui::waiterForm *ui;
};

#endif // WAITERFORM_H
