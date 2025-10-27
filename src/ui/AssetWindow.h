#ifndef ASSETWINDOW_H
#define ASSETWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QCandlestickSeries>
#include "GameAPI.h"

namespace Ui {
class AssetWindow;
}

class AssetWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AssetWindow(GameAPI& api, QString &symbol, QWidget *parent = nullptr);
    ~AssetWindow();
    void updateChart();

private slots:
    void on_buy_butt_clicked();

    void on_cancel_butt_clicked();

    void on_sell_butt_clicked();

private:
    GameAPI& api_;
    QString& symbol_;
    QPushButton *buy_butt;
    QPushButton *sell_butt;
    QPushButton *cancel_butt;
    QChart *chart_;
    QFrame *chartFrame_;
    QChartView *chartView_;
    QVBoxLayout *chartLayout_;
    QCandlestickSeries *series_;
};

#endif // ASSETWINDOW_H
