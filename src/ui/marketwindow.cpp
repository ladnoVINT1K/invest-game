#include "MarketWindow.h"
#include <QHeaderView>

MarketWindow::MarketWindow(GameAPI& api, QWidget *parent)
    : QDialog(parent), api_(api)
{
    setWindowTitle("Рынок активов");
    resize(843, 562);

    marketTable_ = new QTableWidget(this);
    marketTable_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(marketTable_, &QTableWidget::cellClicked, this, &MarketWindow::onMarketCellClicked);
    // если сильно надо, то могу сделать кликабельной всю таблицу ;)

    cancel_butt = new QPushButton("Закрыть", this);
    cancel_butt->setFixedHeight(29);
    connect(cancel_butt, &QPushButton::clicked, this, &MarketWindow::on_cancel_butt_clicked);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(marketTable_);
    mainLayout->addWidget(cancel_butt);

    mainLayout->setContentsMargins(20, 20, 22, 13);

    updateUi();
}

MarketWindow::~MarketWindow() = default;

void MarketWindow::updateUi() {
    auto marketAssets = api_.getMarketAssets();
    QTableWidget *table = marketTable_;

    table->clearContents();
    table->setRowCount(0);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Актив", "Цена", "Тренд", "Волатильность"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (const auto &entry : marketAssets) {
        QString symbol = QString::fromStdString(entry.symbol);
        double price = entry.price;
        double trend = entry.trend;
        double vol = entry.volatility;

        int row = table->rowCount();
        table->insertRow(row);

        QTableWidgetItem *nameItem = new QTableWidgetItem(symbol);
        QFont font;
        font.setBold(true);
        nameItem->setFont(font);

        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(price, 'f', 2));
        QTableWidgetItem *trendItem = new QTableWidgetItem(QString::number(trend * 100, 'f', 2) + "%");
        QTableWidgetItem *volItem = new QTableWidgetItem(QString::number(vol * 100, 'f', 2) + "%");

        bool up = api_.isGrowing(symbol.toStdString());
        nameItem->setForeground(QBrush(up ? Qt::green : Qt::red));

        table->setItem(row, 0, nameItem);
        table->setItem(row, 1, priceItem);
        table->setItem(row, 2, trendItem);
        table->setItem(row, 3, volItem);
    }

    //table->resizeColumnsToContents(); <- мне плохо х2
}

void MarketWindow::onMarketCellClicked(int row, int column) {
    if (column != 0) return;
    QString symbol = marketTable_->item(row, 0)->text();
    AssetWindow asset(api_, symbol, this);
    if (asset.exec() == QDialog::Accepted) {
        updateUi();
    }
}

void MarketWindow::on_cancel_butt_clicked()
{
    QDialog::accept();
}

