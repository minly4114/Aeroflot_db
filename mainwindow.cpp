#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/qsqldatabase.h>
#include "db_connect.h"
#include "authorization.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db_connect *conn = new db_connect();
    db = new QSqlDatabase();
    authorization *auth = new authorization();
    auth->show();
    auth->setDb(db,ui->tw_flight, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_search_clicked()
{
    db_connect *conn = new db_connect();
    conn->searchElem(db, ui->tw_flight, ui->le_searchForElem->text(), ui->cb_searchElem->currentText());
    ui->le_searchForElem->clear();
}

void MainWindow::on_tw_flight_clicked(const QModelIndex &index)
{
    currentFlightId = ui->tw_flight->model()->index(index.row(), 0).data().toString();
    columnFlight=index.column();
}
void MainWindow::on_pb_delete_clicked()
{
    db_connect *conn = new db_connect();
    conn->deleteFlight(currentFlightId, db, ui->tw_flight);
    //conn->uploadingData(db);
}

void MainWindow::on_pb_add_clicked()
{
    db_connect *conn = new db_connect();
    conn->addFlight(db, ui->tw_flight,ui->le_flightNumber->text(),ui->le_boardNumber->text(),ui->le_arrivalTime->text(),ui->le_departureTime->text(),ui->le_dateOfFlight->text(),
                    ui->le_cityOfDeparture->text(), ui->le_cityOfArrival->text());
    ui->le_flightNumber->clear();
    ui->le_boardNumber->clear();
    ui->le_arrivalTime->clear();
    ui->le_departureTime->clear();
    ui->le_dateOfFlight->clear();
}

void MainWindow::on_pb_sortAscending_clicked()
{
    db_connect *conn = new db_connect();
    conn->sortAscending(db, ui->tw_flight, ui->cb_searchElem->currentText());
}

void MainWindow::on_pb_change_clicked()
{
    db_connect *conn = new db_connect();
    conn->changeFlight(db,ui->tw_flight,currentFlightId,columnFlight,ui->le_searchForElem->text());
    ui->le_searchForElem->clear();
}

void MainWindow::on_pb_export_clicked()
{

    saveAsCSV("E:/QtProject/Aeroflot/DataExport.csv");
}

void MainWindow::saveAsCSV(QString filename)
{
    QFile f(filename);

    if( f.open( QIODevice::WriteOnly ) )
    {
        QTextStream ts( &f );
        QStringList strList;

        strList << "\" \"";
        for( int c = 0; c < ui->tw_flight->horizontalHeader()->count(); ++c )
            strList << "\""+ui->tw_flight->model()->headerData(c, Qt::Horizontal).toString()+"\"";
        ts << strList.join( ";" )+"\n";

        for( int r = 0; r < ui->tw_flight->verticalHeader()->count(); ++r )
        {
            strList.clear();
            strList << "\""+ui->tw_flight->model()->headerData(r, Qt::Vertical).toString()+"\"";
            for( int c = 0; c < ui->tw_flight->horizontalHeader()->count(); ++c )
            {
                strList << "\""+ui->tw_flight->model()->data(ui->tw_flight->model()->index(r, c), Qt::DisplayRole).toString()+"\"";
            }
            ts << strList.join( ";" )+"\n";
        }
        f.close();
    }
}

void MainWindow::importFromCSV(QString filename)
{

    /*QFile f(filename);
    if (f.open(QIODevice::ReadOnly)) {

        int lineindex = 0;                     // file line counter
        QTextStream in(&file);                 // read to text stream

        while (!in.atEnd()) {

            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();

            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);

            // load parsed data to model accordingly
            for (int j = 0; j < lineToken.size(); j++) {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                model->setItem(lineindex, j, item);
            }

            lineindex++;
        }

        file.close();
    }
    ui->tw_flight->setModel(model);```// It doesn't work*/
}

void MainWindow::on_pb_import_clicked()
{
    db_connect *conn = new db_connect();
    conn->importFile(db,ui->tw_flight,"E:/QtProject/Aeroflot/temp.csv");
}
