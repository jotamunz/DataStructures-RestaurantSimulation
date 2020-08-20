#ifndef ASSIGNERFORM_H
#define ASSIGNERFORM_H

#include <QWidget>

namespace Ui {
class assignerForm;
}

class assignerForm : public QWidget
{
    Q_OBJECT

public:
    explicit assignerForm(QWidget *parent = nullptr);
    ~assignerForm();

//private:
    Ui::assignerForm *ui;
};

#endif // ASSIGNERFORM_H
