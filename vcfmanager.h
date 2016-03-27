#ifndef VCFMANAGER_H
#define VCFMANAGER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include "parser.h"
#include "dataservice.h"

namespace Ui {
class VCFManager;
}

class VCFManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit VCFManager(QWidget *parent = 0);
    ~VCFManager();

private slots:
    void on_fileopenButton_clicked();

    void on_parseButton_clicked();

    void on_resreshButton_clicked();

    void on_contactsTableView_activated(const QModelIndex &index);

private:
    Ui::VCFManager *ui;
    DataService dataService;
    QSqlTableModel *contacts;
    QSqlTableModel *phones;
};

#endif // VCFMANAGER_H
