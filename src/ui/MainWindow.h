#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include "GameAPI.h"
#include "InputDialog.h"
#include "MarketWindow.h"
#include "AssetWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateUi();

private slots:
    void on_reset_butt_clicked();
    void on_next_butt_clicked();
    void onAssetCellClicked(int row, int column);
    void on_market_butt_clicked();

private:
    QLabel *balanceLabel_;
    QLabel *capitalLabel_;
    QTableWidget *portfolioTable_;
    QPushButton *reset_butt;
    QPushButton *market_butt;
    QPushButton *next_butt;
    GameAPI api_;
};

#endif // MAINWINDOW_H
