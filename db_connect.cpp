#include "db_connect.h"
#include <qsqlquerymodel.h>
#include <QTextStream>
#include <QFile>

db_connect::db_connect()
{

}
void db_connect::uploadingData(QSqlDatabase *db, QString login, QString pass)
{
    *db = QSqlDatabase::addDatabase("QMYSQL", "aeroflot_db");
    db->setDatabaseName("aeroflot_db");
    db->setUserName(login);
    db->setPassword(pass);
    db->setHostName("localhost");
    db->open();
}
void db_connect::bootstrap(QSqlDatabase *db, QTableView *table)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM flight", *db);
    createModel(model, table);
}
void db_connect::searchElem(QSqlDatabase *db, QTableView *table, QString value, QString column)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    if(column=="Номер рейса")
    {
        model->setQuery("select * from flight where flightNumber='" + value + "';", *db);
    }
    else if(column=="Бортовой номер")
    {
        model->setQuery("select * from flight where boardNumber='" + value + "';", *db);
    }
    else if(column=="Время вылета")
    {
        model->setQuery("select * from flight where arrivalTime='" + value + "';", *db);
    }
    else if(column=="Время прилёта")
    {
        model->setQuery("select * from flight where departureTime='" + value + "';", *db);
    }
    else if(column=="Дата полёта")
    {
        model->setQuery("select * from flight where dateOfFlight='" + value + "';", *db);
    }
    createModel(model,table);
}
void db_connect::sortAscending(QSqlDatabase *db, QTableView *table, QString column)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    if(column=="Номер рейса")
    {
        model->setQuery("select* from flight order by(flightNumber) ASC;", *db);
    }
    else if(column=="Бортовой номер")
    {
        model->setQuery("select* from flight order by(boardNumber) ASC;", *db);
    }
    else if(column=="Время вылета")
    {
        model->setQuery("select* from flight order by(arrivalTime) ASC;", *db);
    }
    else if(column=="Время прилёта")
    {
        model->setQuery("select* from flight order by(departureTime) ASC;", *db);
    }
    else if(column=="Дата полёта")
    {
        model->setQuery("select* from flight order by(dateOfFlight) ASC;", *db);
    }
    else if(column=="Город вылета")
    {
        model->setQuery("select* from flight order by(cityOfDeparture) ASC;", *db);
    }
    else if(column=="Город прилёта")
    {
        model->setQuery("select* from flight order by(cityOfArrival) ASC;", *db);
    }
    createModel(model, table);
}
void db_connect::createModel(QSqlQueryModel *model, QTableView *table)
{
    model->setHeaderData(0, Qt::Horizontal, "Номер рейса");
    model->setHeaderData(1, Qt::Horizontal, "Бортовой номер");
    model->setHeaderData(2, Qt::Horizontal, "Время вылета");
    model->setHeaderData(3, Qt::Horizontal, "Время прилёта");
    model->setHeaderData(4, Qt::Horizontal, "Дата полёта");
    model->setHeaderData(5, Qt::Horizontal, "Город вылета");
    model->setHeaderData(6, Qt::Horizontal, "Город прилёта");

    table->setModel(model);
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->setAlternatingRowColors(true);
}
void db_connect::deleteFlight(QString currentFlightId, QSqlDatabase *db, QTableView *table)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("delete from flight where flightNumber='"+currentFlightId +"';", *db);
    bootstrap(db,table);
}

void db_connect::addFlight(QSqlDatabase *db, QTableView *table, QString flightNumber, QString boardNumber, QString arrivalTime, QString departureTime, QString dateOfFlight,QString cityOfDeparture, QString cityOfArrival)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("insert into flight(flightNumber,boardNumber,arrivalTime,departureTime,dateOfFlight,cityOfDeparture,cityOfArrival)values('"+flightNumber +"','"+ boardNumber + "','"+ arrivalTime +"','"+ departureTime +"','"+dateOfFlight +"','"+ cityOfDeparture +"','"+ cityOfArrival +"');", *db);
    bootstrap(db,table);
}
void db_connect::changeFlight(QSqlDatabase *db, QTableView *table, QString currentFlightId, int columnFlight, QString newInfo)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    if(columnFlight==0)
    {
        model->setQuery("UPDATE flight SET flightNumber = '" + newInfo + "' WHERE flightNumber = '" + currentFlightId + "';", *db);
    }
    else if(columnFlight==1)
    {
        model->setQuery("UPDATE flight SET boardNumber = '" + newInfo + "' WHERE flightNumber = '" + currentFlightId + "';", *db);
    }
    else if(columnFlight==2)
    {
        model->setQuery("UPDATE flight SET arrivalTime = '" + newInfo + "' WHERE flightNumber = '" + currentFlightId + "';", *db);
    }
    else if(columnFlight==3)
    {
        model->setQuery("UPDATE flight SET departureTime = '" + newInfo + "' WHERE flightNumber = '" + currentFlightId + "';", *db);
    }
    else if(columnFlight==4)
    {
        model->setQuery("UPDATE flight SET dateOfFlight = '" + newInfo + "' WHERE flightNumber = '" + currentFlightId + "';", *db);
    }
    else if(columnFlight==5)
    {
        model->setQuery("UPDATE flight SET cityOfDeparture = '" + newInfo + "' WHERE flightNumber = '" + currentFlightId + "';", *db);
    }
    else if(columnFlight==6)
    {
        model->setQuery("UPDATE flight SET cityOfArrival = '" + newInfo + "' WHERE flightNumber = '" + currentFlightId + "';", *db);
    }
    bootstrap(db,table);
}
void db_connect::importFile(QSqlDatabase *db, QTableView *table,QString filename)
{
     QFile f(filename);

     if( f.open( QIODevice::ReadOnly ) )
     { while(!f.atEnd())
         {
             QString temp = f.readLine();
             QVector<QString> v;
             int k=0;
             QString s="";
             for(int i=0; i<temp.length(); i++)
             {

                 if(i==temp.length()-1)
                 {
                     v.insert(k,s);
                     k++;
                     s="";
                 }
                 if(temp[i]!=';')
                 {
                    s+=temp[i];
                 }
                else if(temp[i]==';')
                {
                     v.insert(k,s);
                     k++;
                     s="";
                }
             }
             addFlight(db,table,v.at(0),v.at(1),v.at(2),v.at(3),v.at(4),v.at(5),v.at(6));
         }
     }
}

