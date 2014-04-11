#include "detaileddialog.h"
#include "ui_detaileddialog.h"

DetailedDialog::DetailedDialog(QString name, QString consist, QString description, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailedDialog)
{
    ui->setupUi(this);
    ui->name_label->setText(name);
    ui->consist_textBrowser->append(consist);
    ui->description_textBrowser->append(description);
}

DetailedDialog::~DetailedDialog()
{
    delete ui;
}
