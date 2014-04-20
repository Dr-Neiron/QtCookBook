#ifndef DETAILEDDIALOG_H
#define DETAILEDDIALOG_H

#include <QDialog>

namespace Ui {
class DetailedDialog;
}

class DetailedDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DetailedDialog(int id, QString name, QString consist,
                            QString description, QPixmap pic,
                            QWidget *parent = 0);
    ~DetailedDialog();

    void setFavorite();
    void allowEdit();
    void getData(int &id, QString &name, QString &consist, QString &description, QPixmap &pic,
                 QString &imageFormat);
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
