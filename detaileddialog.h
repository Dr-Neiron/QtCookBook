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
    explicit DetailedDialog(int id, QString name, QString consist, QString description, QWidget *parent = 0);
    ~DetailedDialog();

    void setFavorite();
    
signals:
    void addingFavorite(int id);
    void remFavorite(int id);

private slots:
    void on_print_pushButton_clicked();
    void on_addToFav_pushButton_clicked(bool checked);

private:
    Ui::DetailedDialog *ui;
    int id;
};

#endif // DETAILEDDIALOG_H
