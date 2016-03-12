#ifndef VCFMANAGER_H
#define VCFMANAGER_H

#include <QMainWindow>

namespace Ui {
class VCFManager;
}

class VCFManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit VCFManager(QWidget *parent = 0);
    ~VCFManager();

private:
    Ui::VCFManager *ui;
};

#endif // VCFMANAGER_H
