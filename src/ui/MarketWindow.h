#pragma once
#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include "GameAPI.h"

class MarketWindow : public QDialog {
    Q_OBJECT
public:
    explicit MarketWindow(GameAPI &api, QWidget *parent = nullptr);

private slots:
    void onAssetClicked(int row, int col);
    void onCloseClicked();

private:
    void updateTable();

    GameAPI &api_;
    QTableWidget *table_;
    QPushButton *closeButton_;
};
