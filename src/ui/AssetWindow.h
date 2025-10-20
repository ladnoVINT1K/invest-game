#pragma once
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QtCharts/QChartView>
#include <QtCharts/QCandlestickSeries>
#include "GameAPI.h"
#include <QtCharts/QCandlestickSet>

class AssetWindow : public QDialog {
    Q_OBJECT
public:
    AssetWindow(GameAPI &api, const QString &symbol, QWidget *parent = nullptr);

private slots:
    void onBuy();
    void onSell();

private:
    void updateChart();

    GameAPI &api_;
    QString symbol_;
    QLabel *priceLabel_;
    QCandlestickSeries *series_;
    QChartView *chartView_;
    QPushButton *buyButton_;
    QPushButton *sellButton_;
};
