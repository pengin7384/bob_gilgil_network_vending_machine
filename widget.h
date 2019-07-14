#pragma once

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QStringListModel>
#include <QMessageBox>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void loadPbs();
    void loadPrices();
    void loadConnects();
    void loadList();
    void update();
    void on_Clicked();
    void insertCoin(int price);
    void buyItem(int price);
    void reset();
    void addMessage(QString msg);
    void showMessage(QString title, QString msg);
private:
    Ui::Widget *ui;
    int prices[7];
    int total;
    QPushButton *pbs[9];

    // For QListView
    QStringListModel *listModel;
    QStringList *stringList;


};
