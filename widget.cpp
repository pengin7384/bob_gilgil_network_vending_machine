#include "widget.h"
#include "ui_widget.h"

/**
 * @brief Widget::Widget
 * Vending Machine
 * @param parent
 */
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    loadPbs();
    loadPrices();
    loadConnects();
    loadList();
}

Widget::~Widget()
{
    delete ui;
    listModel->removeRows(0, listModel->rowCount());
}

/**
 * @brief Widget::loadPbs
 * Load QPushButtons to pbs
 */
void Widget::loadPbs()
{
    pbs[0] = ui->pb10;
    pbs[1] = ui->pb50;
    pbs[2] = ui->pb100;
    pbs[3] = ui->pb500;
    pbs[4] = ui->pbCoffee;
    pbs[5] = ui->pbMilk;
    pbs[6] = ui->pbTea;
    pbs[7] = ui->pbReset;
    pbs[8] = ui->pbClear;
}

/**
 * @brief Widget::loadPrices
 * Load prices to prices
 */
void Widget::loadPrices()
{
    total = 0;
    prices[0] = 10;
    prices[1] = 50;
    prices[2] = 100;
    prices[3] = 500;
    prices[4] = -100;
    prices[5] = -200;
    prices[6] = -300;

    for(int i=0; i<7; i++) {
        pbs[i]->setWhatsThis(QString::number(prices[i]));
    }

    update();
}


/**
 * @brief Widget::loadConnects
 * Make 'connect' for 'pbs'
 */
void Widget::loadConnects()
{
    for(int i=0; i<9; i++) {
        connect(pbs[i], SIGNAL (released()), this, SLOT (on_Clicked()));
    }
}

/**
 * @brief Widget::loadList
 * Init QStringListModel, QStringList
 */
void Widget::loadList()
{
    listModel = new QStringListModel(this);
    stringList = new QStringList();

    listModel->setStringList(*stringList);
    ui->listView->setModel(listModel);
}


/**
 * @brief Widget::update
 * Update total to UI
 */
void Widget::update()
{
    for(int i=4; i<7; i++) {
        if(prices[i]+total < 0) {
            pbs[i]->setEnabled(false);
        } else {
            pbs[i]->setEnabled(true);
        }
    }
    ui->lcdNumber->display(total);
}

/**
 * @brief Widget::on_Clicked
 * Pbs click event
 */
void Widget::on_Clicked()
{
    QPushButton* btn = ((QPushButton*)sender());

    if(btn == ui->pbReset) { // Reset
        reset();
    } else if(btn == ui->pbClear) {
        listModel->removeRows(0, listModel->rowCount());
    }else { // Insert Coin & Buy Item
        int price = btn->whatsThis().toInt();
        if(price>0) {   // InsertCoin
            insertCoin(price);
        } else {        // BuyItem
            buyItem(price);
        }
    }
    update();
}


/**
 * @brief Widget::insertCoin
 * Insert Coin
 * @param price
 */
void Widget::insertCoin(int price)
{
    total += price;
    addMessage("Insert Coin : " + QString::number(price));
}

/**
 * @brief Widget::buyItem
 * Buy Item
 * @param price
 */
void Widget::buyItem(int price)
{
    if(total + price >= 0) {
        total += price;
    }
    addMessage("Buy Item : " + QString::number(price));
}

/**
 * @brief Widget::reset
 * Make 'total' to 0 & Exchange coin
 */
void Widget::reset()
{
    int index=3;
    int cnt=0;
    QString str;

    while(index>=0) {
        if(total >= prices[index]) {
            total = total - prices[index];
            cnt++;
        } else {
            if(cnt > 0) {
                addMessage("Exchange(" + QString::number(prices[index]) + "): " + QString::number(cnt));
                str = str + QString::number(prices[index]) + ": " + QString::number(cnt) + "\n";
            }
            index--;
            cnt=0;
        }
    }

    if(str.size() > 0) {
        str.resize(str.size()-1);
    }

    showMessage("Exchange", str);
    update();
}

/**
 * @brief Widget::addMessage
 * Add 'msg' to 'ListView'
 * @param msg
 */
void Widget::addMessage(QString msg)
{
    if(listModel->insertRow(listModel->rowCount())) {
        QModelIndex index = listModel->index(listModel->rowCount()-1, 0);
        listModel->setData(index, msg);
    }
}

/**
 * @brief Widget::showMessage
 * Show MessageBox
 * @param title
 * @param msg
 */
void Widget::showMessage(QString title, QString msg)
{
    QMessageBox msgBox;
    msgBox.information(nullptr, title, msg);

}


