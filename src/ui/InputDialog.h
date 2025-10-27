#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QPushButton>

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    ~InputDialog();

    int getCapital() const;

private slots:
    void on_pushButton_clicked();

private:
    QSpinBox *capital_spin;
    QPushButton *pushButton;
};

#endif // INPUTDIALOG_H
