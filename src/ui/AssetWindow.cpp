#include "AssetWindow.h"
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QtCharts/QCandlestickSet>


AssetWindow::AssetWindow(GameAPI &api, const QString &symbol, QWidget *parent)
    : QDialog(parent), api_(api), symbol_(symbol)
{
    setWindowTitle(symbol);
    resize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(this);
    priceLabel_ = new QLabel(this);
    layout->addWidget(priceLabel_);

    series_ = new QCandlestickSeries(this);
    QChart *chart = new QChart();
    chart->addSeries(series_);
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setTitleText("Время");
    chart->axes(Qt::Vertical).first()->setTitleText("Цена");
    chart->setTitle(symbol);

    chartView_ = new QChartView(chart);
    layout->addWidget(chartView_);

    QHBoxLayout *bottom = new QHBoxLayout;
    buyButton_ = new QPushButton("Купить", this);
    sellButton_ = new QPushButton("Продать", this);
    connect(buyButton_, &QPushButton::clicked, this, &AssetWindow::onBuy);
    connect(sellButton_, &QPushButton::clicked, this, &AssetWindow::onSell);
    bottom->addWidget(buyButton_);
    bottom->addWidget(sellButton_);
    layout->addLayout(bottom);

    updateChart();
}

void AssetWindow::updateChart() {
    auto candles = api_.getCandles(symbol_.toStdString());
    series_->clear();

    for (const auto &c : candles) {
        QCandlestickSet *set = new QCandlestickSet(c.open, c.high, c.low, c.close);
        series_->append(set);
    }

    double price = api_.getCurrentPrice(symbol_.toStdString());
    priceLabel_->setText(QString("Цена: %1").arg(price));
    sellButton_->setEnabled(api_.getProfit() > 0.0);
}

void AssetWindow::onBuy() {
    bool ok;
    double amount = QInputDialog::getDouble(this, "Купить", "Сколько вложить:", 1000, 0, 1e9, 2, &ok);
    if (ok) {
        if (amount > api_.getCapital()) {
            QMessageBox::warning(this, "Ошибка", "Недостаточно средств!");
            return;
        }
        api_.buy(symbol_.toStdString(), amount);
        updateChart();
    }
}

void AssetWindow::onSell() {
    bool ok;
    double amount = QInputDialog::getDouble(this, "Продать", "Сколько продать:", 1000, 0, 1e9, 2, &ok);
    if (ok) {
        api_.sell(symbol_.toStdString(), amount);
        updateChart();
    }
}
