#ifndef STARTUPFORM_H
#define STARTUPFORM_H

#include <QWidget>

namespace Ui {
class StartupForm;
}

class StartupForm : public QWidget
{
    Q_OBJECT

public:
    explicit StartupForm(QWidget *parent = nullptr);
    ~StartupForm();

    int tableCount;
    int waiterCount;

private slots:
    void on_pushButton_Conf_clicked();

private:
    Ui::StartupForm *ui;
};

#endif // STARTUPFORM_H
