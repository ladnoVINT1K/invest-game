#pragma once
#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include "GameAPI.h"

class MarketWindow;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onNextMonth();
    void onOpenMarket();
    void onAssetClicked(int row, int col);
    void updateUI();

private:
    GameAPI api_;
    QTableWidget *portfolioTable_;
    QLabel *balanceLabel_;
    QLabel *capitalLabel_;
    QPushButton *nextButton_;
    QPushButton *marketButton_;
    MarketWindow *marketWindow_;
};
