#include "MarketWindow.h"
#include "AssetWindow.h"
#include <QVBoxLayout>
#include <QHeaderView>

MarketWindow::MarketWindow(GameAPI &api, QWidget *parent)
    : QDialog(parent), api_(api)
{
    setWindowTitle("Рынок активов");
    resize(700, 500);

    QVBoxLayout *layout = new QVBoxLayout(this);

    table_ = new QTableWidget(this);
    table_->setColumnCount(4);
    table_->setHorizontalHeaderLabels({"Актив", "Цена", "Тренд", "Волатильность"});
    table_->horizontalHeader()->setStretchLastSection(true);
    table_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(table_, &QTableWidget::cellClicked, this, &MarketWindow::onAssetClicked);

    closeButton_ = new QPushButton("Закрыть", this);
    connect(closeButton_, &QPushButton::clicked, this, &MarketWindow::onCloseClicked);

    layout->addWidget(table_);
    layout->addWidget(closeButton_);

    updateTable();
}

void MarketWindow::updateTable() {
    auto assets = api_.getMarketAssets();

    table_->setRowCount(0);
    for (const auto &a : assets) {
        QString symbol = QString::fromStdString(a.symbol);
        double price = a.price;
        double trend = a.trend;
        double vol = a.volatility;

        int row = table_->rowCount();
        table_->insertRow(row);

        QTableWidgetItem *nameItem = new QTableWidgetItem(symbol);
        QFont font;
        font.setBold(true);
        nameItem->setFont(font);

        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(price, 'f', 2));
        QTableWidgetItem *trendItem = new QTableWidgetItem(QString::number(trend * 100, 'f', 2) + "%");
        QTableWidgetItem *volItem = new QTableWidgetItem(QString::number(vol * 100, 'f', 2) + "%");

        bool up = api_.isGrowing(symbol.toStdString());
        nameItem->setForeground(QBrush(up ? Qt::green : Qt::red));

        table_->setItem(row, 0, nameItem);
        table_->setItem(row, 1, priceItem);
        table_->setItem(row, 2, trendItem);
        table_->setItem(row, 3, volItem);
    }
}

void MarketWindow::onAssetClicked(int row, int col) {
    QString symbol = table_->item(row, 0)->text();
    AssetWindow *window = new AssetWindow(api_, symbol, this);
    window->show();
}

void MarketWindow::onCloseClicked() {
    close();
}
