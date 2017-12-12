#include "authorization.h"
#include "ui_authorization.h"
#include <QtSql/qsqldatabase.h>
#include "db_connect.h"

authorization::authorization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
    db_connect *conn = new db_connect();
}

authorization::~authorization()
{
    delete ui;
}
void authorization::setDb(QSqlDatabase *database,QTableView *table, MainWindow  *mainw)
{
    db = database;
    newtable= table;
    newmainw = mainw;
}

void authorization::on_pb_enter_clicked()
{
    db_connect *conn = new db_connect();
    conn->uploadingData(db, ui->le_login->text(), ui->le_pass->text());
    conn->bootstrap(db, newtable);
    newmainw->show();
    this->close();
}
