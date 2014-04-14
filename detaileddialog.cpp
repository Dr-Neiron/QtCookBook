#include "detaileddialog.h"
#include "ui_detaileddialog.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QDebug>

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

void DetailedDialog::on_print_pushButton_clicked()
{
    QString textData;
    textData.append(ui->name_label->text());
    textData.append(ui->consist_textBrowser->toHtml());
    textData.append(ui->description_textBrowser->toHtml());

    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog pd(&printer, this);
    pd.setWindowTitle(tr("Print reciept"));
    QTextEdit te(this);
    te.setHtml(textData);

    if (QDialog::Accepted == pd.exec())
        te.print(&printer);
}
