#ifndef DETAILEDDIALOG_H
#define DETAILEDDIALOG_H

#include <QDialog>
#include "defines.h"

namespace Ui {
class DetailedDialog;
}

class DetailedDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DetailedDialog(Defines::dish_t dish, QWidget *parent = 0);
    ~DetailedDialog();

    void setFavorite();
    void allowEdit();
    void getData(Defines::dish_t &dish, QString &imageFormat);
    bool imageWasUpdated();
    
signals:
    void addingFavorite(int id);
    void remFavorite(int id);

private slots:
    void on_print_pushButton_clicked();
    void on_addToFav_pushButton_clicked(bool checked);
    void on_uploadImage_pushButton_clicked();

private:
    Ui::DetailedDialog *ui;
    QString     imageFormat;
    int         id;
    bool        imageUpdated;
};

#endif // DETAILEDDIALOG_H
