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
    explicit DetailedDialog(QString name, QString consist, QString description, QWidget *parent = 0);
    ~DetailedDialog();
    
private slots:
    void on_print_pushButton_clicked();

private:
    Ui::DetailedDialog *ui;
};

#endif // DETAILEDDIALOG_H
