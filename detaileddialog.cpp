#include "detaileddialog.h"
#include "ui_detaileddialog.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QDebug>

DetailedDialog::DetailedDialog(Defines::dish_t dish, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailedDialog)
{
    ui->setupUi(this);
    ui->name_label->setText(dish.name);
    ui->name_lineEdit->setText(dish.name);
    ui->name_lineEdit->setVisible(false);
    ui->consist_plainTextEdit->appendPlainText(dish.consist);
    ui->description_plainTextEdit->appendPlainText(dish.description);
    ui->vegetarian_checkBox->setChecked(dish.isVegetarian);
    ui->vegetarian_checkBox->setEnabled(false);
    if (!dish.pixmap.isNull())
        ui->image_label->setPixmap(dish.pixmap.scaled(ui->image_label->size()));
    this->id = dish.id;
    ui->uploadImage_pushButton->setVisible(false);
    imageUpdated = false;
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
    ui->uploadImage_pushButton->setVisible(true);
    ui->vegetarian_checkBox->setEnabled(true);
}

void DetailedDialog::getData(Defines::dish_t &dish, QString &imageFormat)
{
    dish.id = this->id;
    dish.name = ui->name_lineEdit->text();
    dish.consist = ui->consist_plainTextEdit->toPlainText();
    dish.description = ui->description_plainTextEdit->toPlainText();
    if (ui->image_label->pixmap() != NULL)
        dish.pixmap = *(ui->image_label->pixmap());
    imageFormat = this->imageFormat;
    dish.isVegetarian = ui->vegetarian_checkBox->isChecked();
}

bool DetailedDialog::imageWasUpdated()
{
    return imageUpdated;
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

void DetailedDialog::on_uploadImage_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image file"),
                                                        qApp->applicationDirPath(),
                                                        tr("Images (*.bmp *.jpg *.jpeg *.gif *.png *.xpm)"));
    imageFormat = fileName.split(".").last();
    if (fileName.isEmpty())
        return;
    QPixmap pic(fileName);
    if (!pic.isNull())
    {
        ui->image_label->setPixmap(pic.scaled(ui->image_label->size()));
        imageUpdated = true;
    }
}
