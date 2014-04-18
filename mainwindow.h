#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "defines.h"
#include "filter.h"
#include "userfavorites.h"
#include <QMainWindow>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRelationalTableModel>

namespace Ui {
class MainWindow;
}

using namespace Defines;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_login_pushButton_clicked();
    void on_logout_pushButton_clicked();
    void on_main_tableView_doubleClicked(const QModelIndex &index);
    void on_reset_pushButton_clicked();
    void on_types_comboBox_currentIndexChanged(int index);
    void on_season_comboBox_currentIndexChanged(int index);
    void on_contry_comboBox_currentIndexChanged(int index);
    void on_vegetarian_pushButton_toggled(bool checked);
    void on_favorite_pushButton_clicked(bool checked);
    void on_spinBox_valueChanged(int arg1);
    void on_random_pushButton_clicked();
    void on_register_pushButton_clicked();
    void on_about_triggered();
    void on_main_tableView_customContextMenuRequested(const QPoint &pos);

    void on_add_pushButton_clicked();

    void on_del_pushButton_clicked();

    void on_save_pushButton_clicked();

    void on_pucancel_shButton_clicked();

private:
    Ui::MainWindow              *ui;
    QSqlDatabase                db;
    QSqlRelationalTableModel    *model;
    Filter                      filterClass;
    UserFavorites               favorites;
    bool                        isAdminLoggedIn;
    QString                     userName;

    void adminLogin();
    void userLogin();
    void applyFilter(filters_t filter, int id);
    void prepareModel();
};

#endif // MAINWINDOW_H
