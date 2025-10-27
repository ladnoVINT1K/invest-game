#ifndef MARKETWINDOW_H
#define MARKETWINDOW_H

#include <QDialog>
#include "GameAPI.h"
#include <QPushButton>
#include <QTableWidget>
#include "assetwindow.h"


class MarketWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MarketWindow(GameAPI& api, QWidget *parent = nullptr);
    ~MarketWindow();
    void updateUi();

private slots:
    void on_cancel_butt_clicked();
    void onMarketCellClicked(int row, int column);

private:
    QTableWidget *marketTable_;
    QPushButton *cancel_butt;
    GameAPI& api_;
};

#endif // MARKETWINDOW_H
