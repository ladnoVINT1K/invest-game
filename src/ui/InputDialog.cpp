#include "InputDialog.h"
#include <QHBoxLayout>

InputDialog::InputDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Ввести капитал");
    resize(833, 328);

    capital_spin = new QSpinBox(this);
    capital_spin->setMaximum(1000000000);
    capital_spin->setFixedWidth(261);
    capital_spin->setFixedHeight(29);

    pushButton = new QPushButton("ОК", this);
    pushButton->setFixedSize(111, 31);
    connect(pushButton, &QPushButton::clicked, this, &InputDialog::on_pushButton_clicked);

    QHBoxLayout *spinLayout = new QHBoxLayout();
    spinLayout->addStretch();
    spinLayout->addWidget(capital_spin);
    spinLayout->addStretch();

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(pushButton);
    buttonLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(spinLayout);
    mainLayout->addSpacing(21);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
}

InputDialog::~InputDialog() = default;

void InputDialog::on_pushButton_clicked()
{
    QDialog::accept();
}

int InputDialog::getCapital() const
{
    return capital_spin->value();
}

