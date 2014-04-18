#include "detaileddialog.h"
#include "ui_detaileddialog.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QDebug>

DetailedDialog::DetailedDialog(int id, QString name, QString consist, QString description, QPixmap pic, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailedDialog)
{
    ui->setupUi(this);
    ui->name_label->setText(name);
    ui->name_lineEdit->setText(name);
    ui->name_lineEdit->setVisible(false);
    ui->consist_plainTextEdit->appendPlainText(consist);
    ui->description_plainTextEdit->appendPlainText(description);
    if (!pic.isNull())
        ui->image_label->setPixmap(pic);
    this->id = id;
}

DetailedDialog::~DetailedDialog()
{
    delete ui;
}

void DetailedDialog::setFavorite()
{
    ui->addToFav_pushButton->setChecked(true);
    ui->addToFav_pushButton->setText(tr("Remove from favorites"));
}

void DetailedDialog::allowEdit()
{
    ui->consist_plainTextEdit->setReadOnly(false);
    ui->description_plainTextEdit->setReadOnly(false);
    ui->name_label->setVisible(false);
    ui->name_lineEdit->setVisible(true);
}

void DetailedDialog::getData(int &id, QString &name, QString &consist, QString &description, QPixmap &pic)
{
    id = this->id;
    name = ui->name_lineEdit->text();
    consist = ui->consist_plainTextEdit->toPlainText();
    description = ui->description_plainTextEdit->toPlainText();
    pic = QPixmap(); // TODO: implement pixmap
}

void DetailedDialog::on_print_pushButton_clicked()
{
    QString textData;
    textData.append(ui->name_label->text());
    textData.append(tr("Consistence:"));
    textData.append(ui->consist_plainTextEdit->toPlainText());
    textData.append(tr("Description"));
    textData.append(ui->description_plainTextEdit->toPlainText());

    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog pd(&printer, this);
    pd.setWindowTitle(tr("Print reciept"));
    QTextEdit te(this);
    te.setHtml(textData);

    if (QDialog::Accepted == pd.exec())
        te.print(&printer);
}

void DetailedDialog::on_addToFav_pushButton_clicked(bool checked)
{
    if (checked)
    {
        emit addingFavorite(id);
        ui->addToFav_pushButton->setText(tr("Remove from favorites"));
    }
    else
    {
        emit remFavorite(id);
        ui->addToFav_pushButton->setText(tr("To favorites"));
    }
}
