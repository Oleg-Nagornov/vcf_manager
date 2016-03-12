#include "vcfmanager.h"
#include "ui_vcfmanager.h"

VCFManager::VCFManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VCFManager)
{
    ui->setupUi(this);
}

VCFManager::~VCFManager()
{
    delete ui;
}
