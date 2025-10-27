#include "AssetWindow.h"
#include <QtCharts/QChart>
#include <QtCharts/QCandlestickSet>
#include <QtCharts/QValueAxis>
#include <QDebug>
#include <QRandomGenerator>
#include <QInputDialog>
#include <QMessageBox>

AssetWindow::AssetWindow(GameAPI& api, QString &symbol, QWidget *parent)
    : QDialog(parent), api_(api), symbol_(symbol)
{
    setWindowTitle("График свечей");
    resize(964, 615);

    buy_butt = new QPushButton("Купить", this);
    buy_butt->setFixedSize(191, 41);

    sell_butt = new QPushButton("Продать", this);
    sell_butt->setFixedSize(191, 41);

    cancel_butt = new QPushButton("Закрыть", this);
    cancel_butt->setFixedSize(191, 41);

    connect(buy_butt, &QPushButton::clicked, this, &AssetWindow::on_buy_butt_clicked);
    connect(sell_butt, &QPushButton::clicked, this, &AssetWindow::on_sell_butt_clicked);
    connect(cancel_butt, &QPushButton::clicked, this, &AssetWindow::on_cancel_butt_clicked);

    chartFrame_ = new QFrame(this);
    chartFrame_->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    chartFrame_->setFixedSize(921, 521);

    chartLayout_ = new QVBoxLayout(chartFrame_);
    chartLayout_->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(buy_butt);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(sell_butt);
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancel_butt);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(chartFrame_);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setContentsMargins(20, 10, 23, 10);

    chart_ = new QChart();
    //chart_->setTitle("Свечной график актива"); <- мне не нравится как с названием выглядит -_-
    chart_->setAnimationOptions(QChart::SeriesAnimations);
    chart_->legend()->setVisible(true);
    chart_->legend()->setAlignment(Qt::AlignBottom);

    series_ = new QCandlestickSeries();
    series_->setName(symbol_);
    series_->setIncreasingColor(Qt::green);
    series_->setDecreasingColor(Qt::red);

    chart_->addSeries(series_);

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Время");
    axisX->setLabelFormat("%d");
    axisX->setTickCount(series_->count() + 1);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Цена");
    chart_->addAxis(axisX, Qt::AlignBottom);
    chart_->addAxis(axisY, Qt::AlignLeft);
    series_->attachAxis(axisX);
    series_->attachAxis(axisY);

    chartView_ = new QChartView(chart_);
    chartView_->setRenderHint(QPainter::Antialiasing);
    chartView_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    chartLayout_->addWidget(chartView_);

    updateChart();

}

AssetWindow::~AssetWindow() = default;

void AssetWindow::updateChart() {
    series_->clear();
    series_->setBodyWidth(0.2);
    double i = 0;
    auto candles = api_.getCandles(symbol_.toStdString());
    for (const auto &c : candles) {
        series_->append(new QCandlestickSet(c.open, c.high, c.low, c.close, i));
        i += 1;
    }

    if (series_->count() > 0) {
        qreal minLow = series_->sets().first()->low();
        qreal maxHigh = series_->sets().first()->high();
        for (const auto *candle : series_->sets()) {
            minLow = qMin(minLow, candle->low());
            maxHigh = qMax(maxHigh, candle->high());
        }
        static_cast<QValueAxis*>(chart_->axisY())->setRange(minLow * 0.98, maxHigh * 1.02);
        //подгон под значения оси у

        qreal minX = series_->sets().first()->timestamp();
        qreal maxX = series_->sets().last()->timestamp();
        static_cast<QValueAxis*>(chart_->axisX())->setRange(minX - 1, maxX + 1);
        //подгон оси x
    }
}

void AssetWindow::on_buy_butt_clicked() /*<- позаимствовала у вас(ну как в целом весь фронт, просто писала своими ручками),
                                                 потому что мне лень думать*/
{
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


void AssetWindow::on_cancel_butt_clicked()
{
    QDialog::accept();
}


void AssetWindow::on_sell_butt_clicked()
{
    bool ok;
    double amount = QInputDialog::getDouble(this, "Продать", "Сколько продать:", 1000, 0, 1e9, 2, &ok);
    if (ok) {
        api_.sell(symbol_.toStdString(), amount);
        updateChart();
    }
}

