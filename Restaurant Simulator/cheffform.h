#ifndef CHEFFFORM_H
#define CHEFFFORM_H

#include <QWidget>

namespace Ui {
class cheffForm;
}

class cheffForm : public QWidget
{
    Q_OBJECT

public:
    explicit cheffForm(QWidget *parent = nullptr);
    ~cheffForm();

//private:
    Ui::cheffForm *ui;
};

#endif // CHEFFFORM_H
