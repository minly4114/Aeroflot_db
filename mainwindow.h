#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "db_connect.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSqlDatabase *db;
    QString currentFlightId;
    int columnFlight;

private slots:
    void on_pb_search_clicked();

    void on_tw_flight_clicked(const QModelIndex &index);

    void on_pb_delete_clicked();

    void on_pb_add_clicked();

    void on_pb_sortAscending_clicked();

    void on_pb_change_clicked();

    void on_pb_export_clicked();

    void saveAsCSV(QString filename);

    void importFromCSV(QString filename);

    void on_pb_import_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
