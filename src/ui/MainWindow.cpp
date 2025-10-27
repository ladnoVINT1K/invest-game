#include "mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), api_()
{

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    portfolioTable_ = new QTableWidget(0, 0, this);
    portfolioTable_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(portfolioTable_, &QTableWidget::cellClicked, this, &MainWindow::onAssetCellClicked);

    reset_butt = new QPushButton("reset", this);
    market_butt = new QPushButton("Рынок", this);
    next_butt = new QPushButton("Следующий месяц", this);

    balanceLabel_ = new QLabel(this);
    capitalLabel_ = new QLabel(this);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(reset_butt);
    buttonLayout->addStretch();
    buttonLayout->addWidget(market_butt);
    buttonLayout->addWidget(next_butt);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(balanceLabel_);
    mainLayout->addWidget(capitalLabel_);
    mainLayout->addWidget(portfolioTable_);
    mainLayout->addLayout(buttonLayout);

    connect(reset_butt, &QPushButton::clicked, this, &MainWindow::on_reset_butt_clicked);
    connect(market_butt, &QPushButton::clicked, this, &MainWindow::on_market_butt_clicked);
    connect(next_butt, &QPushButton::clicked, this, &MainWindow::on_next_butt_clicked);

    setWindowTitle("Инвестиционный портфель");
    resize(800, 600);

    statusBar();
    menuBar();
    updateUi();
}

MainWindow::~MainWindow() = default;

void MainWindow::updateUi() {
    auto portfolio = api_.getPortfolio();
    QTableWidget *table = portfolioTable_;

    balanceLabel_->setText(QString("Деньги: %1").arg(api_.getCapital()));
    capitalLabel_->setText(QString("Капитализация: %1").arg(api_.getCapital() + api_.getProfit()));

    table->clearContents();
    table->setRowCount(0);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Актив", "Amount", "Profit", "Rate"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (auto &entry : portfolio) {
        QString symbol = QString::fromStdString(entry.first);
        double amount = entry.second["amount"];
        double profit = entry.second["profit"];
        double rate = entry.second["rate"];
        int row = table->rowCount();
        table->insertRow(row);

        QTableWidgetItem *nameItem = new QTableWidgetItem(symbol);
        QTableWidgetItem *amountItem = new QTableWidgetItem(QString::number(amount, 'f', 2));
        QTableWidgetItem *profitItem = new QTableWidgetItem(QString::number(profit, 'f', 2));
        QTableWidgetItem *rateItem = new QTableWidgetItem(QString::number(rate, 'f', 2));
        QFont font;
        font.setBold(true);
        nameItem->setFont(font);

        bool up = api_.isGrowing(symbol.toStdString());
        nameItem->setForeground(QBrush(up ? Qt::green : Qt::red));

        table->setItem(row, 0, nameItem);
        table->setItem(row, 1, amountItem);
        table->setItem(row, 2, profitItem);
        table->setItem(row, 3, rateItem);
    }
}

void MainWindow::on_reset_butt_clicked() {
    InputDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        capital_ = dialog.getCapital();
        updateUi();
        //api_.reset();
        //свечи после этой функции не рисуются, господин
    }
}

void MainWindow::onAssetCellClicked(int row, int column) {
    if (column != 0) return;
    QString symbol = portfolioTable_->item(row, 0)->text();
    qDebug() << symbol << '\n';
    AssetWindow asset(api_, symbol, this);
    if (asset.exec() == QDialog::Accepted) {
        updateUi();
    }
}

void MainWindow::on_next_butt_clicked()
{
    api_.nextStep();
    updateUi();
}

void MainWindow::on_market_butt_clicked()
{
    MarketWindow market(api_, this);
    if (market.exec() == QDialog::Accepted) {
        updateUi();
    }
}

