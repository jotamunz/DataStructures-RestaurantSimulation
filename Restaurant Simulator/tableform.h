#ifndef TABLEFORM_H
#define TABLEFORM_H

#include <QWidget>

namespace Ui {
class tableForm;
}

class tableForm : public QWidget
{
    Q_OBJECT

public:
    explicit tableForm(QWidget *parent = nullptr);
    ~tableForm();

//private:
    Ui::tableForm *ui;
};

#endif // TABLEFORM_H
