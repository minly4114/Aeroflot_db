#ifndef DB_CONNECT_H
#define DB_CONNECT_H
#include <qsqldatabase.h>
#include <qsqlquerymodel.h>
#include "qtableview.h"


class db_connect
{
public:
    db_connect();
    void uploadingData(QSqlDatabase *db, QString login, QString pass);
    void bootstrap(QSqlDatabase *db, QTableView *table);
    void searchElem(QSqlDatabase *db, QTableView *table, QString value, QString column);
    void sortAscending(QSqlDatabase *db, QTableView *table, QString column);
    void deleteFlight(QString currentFlightId, QSqlDatabase *db, QTableView *table);
    void addFlight(QSqlDatabase *db, QTableView *table, QString flightNumber, QString boardNumber, QString arrivalTime,
                   QString departureTime, QString dateOfFlight, QString cityOfDeparture, QString cityOfArrival);
    void changeFlight(QSqlDatabase *db, QTableView *table, QString currentFlightId, int columnFlight, QString newInfo);
    void importFile(QSqlDatabase *db,QTableView *table,QString filename);
private:
    void createModel(QSqlQueryModel *model, QTableView *table);
};


#endif // DB_CONNECT_H
