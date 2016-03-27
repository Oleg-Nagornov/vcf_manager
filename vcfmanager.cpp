#include "vcfmanager.h"
#include "ui_vcfmanager.h"

VCFManager::VCFManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VCFManager)
{
    ui->setupUi(this);
    ui->parseButton->setDisabled(true);

    this->contacts = NULL;
}

VCFManager::~VCFManager()
{
    delete ui;
    if (this->contacts != NULL)
    {
        delete this->contacts;
    }

    if (this->phones != NULL)
    {
        delete this->phones;
    }
}

void VCFManager::on_fileopenButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выберите файл контактов");
    this->ui->filenameEdit->setText(filename);
    if (QFile::exists(filename)) {
        this->ui->parseButton->setEnabled(true);
    }
}

void VCFManager::on_parseButton_clicked()
{
    Parser *parser = new Parser(this);
    QVector<Contact> contacts = parser->parseFile(this->ui->filenameEdit->text());
    delete parser;

    for (int i = 0; i < contacts.size(); i++)
    {
        this->dataService.save(contacts[i]);
    }
}

void VCFManager::on_resreshButton_clicked()
{
    if (this->contacts != NULL)
    {
        delete this->contacts;
    }

    this->contacts = new QSqlTableModel(this, this->dataService.getDb());
    this->contacts->setTable("contacts");
    this->contacts->setEditStrategy(QSqlTableModel::OnFieldChange);
    this->contacts->select();

    this->ui->contactsTableView->setModel(this->contacts);
}


void VCFManager::on_contactsTableView_activated(const QModelIndex &index)
{

    if (this->phones != NULL)
    {
        delete this->phones;
    }
    QModelIndex idIndex = this->contacts->index(index.row(), 0);
    this->phones = new QSqlTableModel(this, this->dataService.getDb());
    this->phones->setTable("phones");
    this->phones->setFilter("contact_id = " + this->contacts->data(idIndex).toString());

    this->phones->setEditStrategy(QSqlTableModel::OnFieldChange);
    this->phones->select();


    this->ui->phonesTableView->setModel(this->phones);

}
