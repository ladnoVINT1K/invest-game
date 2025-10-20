#include "MainWindow.h"
#include "MarketWindow.h"
#include "AssetWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QMainWindow>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), marketWindow_(nullptr), api_()
{
    setWindowTitle("Investment Manager");
    resize(900, 600);

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    // Верх: баланс и капитал
    balanceLabel_ = new QLabel(this);
    capitalLabel_ = new QLabel(this);
    QHBoxLayout *topBar = new QHBoxLayout;
    topBar->addWidget(balanceLabel_);
    topBar->addStretch();
    topBar->addWidget(capitalLabel_);

    // Таблица портфеля
    portfolioTable_ = new QTableWidget(this);
    portfolioTable_->setColumnCount(2);
    portfolioTable_->setHorizontalHeaderLabels({"Актив", "Цена"});
    portfolioTable_->horizontalHeader()->setStretchLastSection(true);
    connect(portfolioTable_, &QTableWidget::cellClicked, this, &MainWindow::onAssetClicked);

    // Нижние кнопки
    QHBoxLayout *bottomBar = new QHBoxLayout;
    nextButton_ = new QPushButton("Следующий месяц", this);
    marketButton_ = new QPushButton("Рынок", this);
    connect(nextButton_, &QPushButton::clicked, this, &MainWindow::onNextMonth);
    connect(marketButton_, &QPushButton::clicked, this, &MainWindow::onOpenMarket);
    bottomBar->addWidget(marketButton_);
    bottomBar->addStretch();
    bottomBar->addWidget(nextButton_);

    layout->addLayout(topBar);
    layout->addWidget(portfolioTable_);
    layout->addLayout(bottomBar);
    setCentralWidget(central);

    updateUI();
}

void MainWindow::updateUI() {
    auto portfolio = api_.getPortfolio();
    auto marketAssets = api_.getMarketAssets();

    balanceLabel_->setText(QString("💵 Деньги: %1").arg(api_.getCapital()));
    capitalLabel_->setText(QString("💰 Капитализация: %1").arg(api_.getCapital() + api_.getProfit()));

    portfolioTable_->setRowCount(0);
    for (const auto &entry : marketAssets) {
        QString symbol = QString::fromStdString(entry.symbol);
        double price = entry.price;
        bool up = api_.isGrowing(symbol.toStdString());

        int row = portfolioTable_->rowCount();
        portfolioTable_->insertRow(row);

        QTableWidgetItem *nameItem = new QTableWidgetItem(symbol);
        QFont font;
        font.setBold(true);
        nameItem->setFont(font);
        nameItem->setForeground(QBrush(up ? Qt::green : Qt::red));

        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(price, 'f', 2));
        portfolioTable_->setItem(row, 0, nameItem);
        portfolioTable_->setItem(row, 1, priceItem);
    }

}

void MainWindow::onNextMonth() {
    api_.nextStep();
    updateUI();
}

void MainWindow::onOpenMarket() {
    if (!marketWindow_)
        marketWindow_ = new MarketWindow(api_, this);
    marketWindow_->show();
    marketWindow_->raise();
}

void MainWindow::onAssetClicked(int row, int col) {
    QString symbol = portfolioTable_->item(row, 0)->text();
    AssetWindow *window = new AssetWindow(api_, symbol, this);
    window->show();
}
