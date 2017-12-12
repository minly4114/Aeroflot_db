#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H
#include <QMainWindow>
#include "db_connect.h"
#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class authorization;
}

class authorization : public QWidget
{
    Q_OBJECT

public:
    explicit authorization(QWidget *parent = 0);
    ~authorization();
    void setDb(QSqlDatabase *database, QTableView *table, MainWindow *mainw);
    QTableView *newtable;
    QSqlDatabase *db;
    MainWindow *newmainw;

private slots:
    void on_pb_enter_clicked();

private:
    Ui::authorization *ui;
};

#endif // AUTHORIZATION_H
