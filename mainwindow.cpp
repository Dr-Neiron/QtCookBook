#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "detaileddialog.h"
#include <QMessageBox>
#include <QtSql/QSqlRelation>
#include <QtSql/QSqlQuery>
#include <QModelIndexList>
#include <QModelIndex>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/msuldun/Qt/Kursovik_bluda/app.db");
    if (!db.open())
    {
        QMessageBox::critical(this, tr("Database error"), tr("Can't open database"));
        return;
    }
    statusBar()->showMessage(tr("Database opened"), 5000);

    prepareModel();

    isAdminLoggedIn = false;
}

MainWindow::~MainWindow()
{
    if (db.isOpen())
        db.close();
    if (model)
        delete model;
    delete ui;
}

void MainWindow::on_login_pushButton_clicked()
{
    userName = ui->login_lineEdit->text();
    QString pass = ui->password_lineEdit->text();
    QSqlQuery query;
    query.exec(QString("SELECT role FROM users WHERE name = '%1' AND pass = '%2'")
               .arg(userName)
               .arg(pass));

    if (query.next())
    {
        bool ok;
        switch (query.value(0).toInt(&ok))
        {
        case ADMINISTRATOR_ROLE:
            adminLogin();
            break;
        case USER_ROLE:
            userLogin();
            break;
        default:
            qDebug() << "wrong role for user " << userName;
        }
    }
    else
        QMessageBox::information(this, tr("Login incorrect"), tr("Login name or password is incorrect"));
}

void MainWindow::adminLogin()
{
    userLogin();
    //features for admin
}

void MainWindow::userLogin()
{
    ui->login_stackedWidget->setCurrentIndex(1);
    ui->userName_label->setText(userName);
    loadMainTable();
}

void MainWindow::loadMainTable()
{
    model->select();
    ui->main_tableView->setItemDelegate(new QSqlRelationalDelegate(ui->main_tableView));
    ui->main_tableView->hideColumn(0);
    ui->main_tableView->hideColumn(8);

    ui->main_tableView->setColumnWidth(0,20);
    ui->main_tableView->setColumnWidth(1,150);
    ui->main_tableView->setColumnWidth(2,150);
    ui->main_tableView->setColumnWidth(3,200);
    ui->main_tableView->setColumnWidth(4,100);
    ui->main_tableView->setColumnWidth(5,100);
    ui->main_tableView->setColumnWidth(6,100);
    ui->main_tableView->setColumnWidth(7,100);
    ui->main_tableView->setColumnWidth(8,20);
    ui->main_tableView->setColumnWidth(9,60);
}

void MainWindow::applyFilter(filters_t filter, int id)
{
    switch (filter)
    {
    case SEASON_FILTER:
    case TYPES_FILTER:
    case CONTRY_FILTER:
    case VEGETARIAN_FILTER:
    {
        QModelIndex index = model->relationModel(filter)->index(id, 0);
        filterClass.applyNew(filter, index.data().toString());
        break;
    }
    case DURATION_FILTER:
        filterClass.applyNew(filter, QString::number(id,10));
        break;
    default:
        qDebug() << "Error argument in applyFilter(...) call:" << filter;
        return;
    };

    if (0 == id)
        filterClass.resetFilter(filter);
    model->setFilter(filterClass.currentFilter());
}

void MainWindow::prepareModel()
{
    model = new QSqlRelationalTableModel(this,db);
    model->setTable("bluda");
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    model->setRelation(5,QSqlRelation("seasons", "id", "name"));
    model->setRelation(6,QSqlRelation("types", "id", "name"));
    model->setRelation(7,QSqlRelation("contries", "id", "name"));
    model->setRelation(9,QSqlRelation("bool_values", "val", "name"));

    model->setHeaderData( 0, Qt::Horizontal, tr("Product ID") );
    model->setHeaderData( 1, Qt::Horizontal, tr("Product name") );
    model->setHeaderData( 2, Qt::Horizontal, tr("Composition") );
    model->setHeaderData( 3, Qt::Horizontal, tr("Description") );
    model->setHeaderData( 4, Qt::Horizontal, tr("Duration") );
    model->setHeaderData( 5, Qt::Horizontal, tr("Season") );
    model->setHeaderData( 6, Qt::Horizontal, tr("Type") );
    model->setHeaderData( 7, Qt::Horizontal, tr("Contry") );
    model->setHeaderData( 8, Qt::Horizontal, tr("Photo") );
    model->setHeaderData( 9, Qt::Horizontal, tr("Vegetarian") );

    ui->main_tableView->setModel(model);
    ui->main_tableView->setSortingEnabled(false);
    ui->main_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->main_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->main_tableView->setShowGrid(true);
    ui->main_tableView->setAlternatingRowColors(true);
    ui->main_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->season_comboBox->setDisabled(true);
    ui->types_comboBox->setDisabled(true);
    ui->season_comboBox->setDisabled(true);
    ui->season_comboBox->setModel(model->relationModel(5));
    ui->season_comboBox->setModelColumn(1);
    ui->types_comboBox->setModel(model->relationModel(6));
    ui->types_comboBox->setModelColumn(1);
    ui->contry_comboBox->setModel(model->relationModel(7));
    ui->contry_comboBox->setModelColumn(1);
    ui->season_comboBox->setDisabled(false);
    ui->types_comboBox->setDisabled(false);
    ui->season_comboBox->setDisabled(false);
}

void MainWindow::on_logout_pushButton_clicked()
{
    ui->login_stackedWidget->setCurrentIndex(0);
    ui->login_lineEdit->clear();
    ui->password_lineEdit->clear();
    // logout features
}

void MainWindow::on_main_tableView_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index)

    QItemSelectionModel * ism = ui->main_tableView->selectionModel();
    QModelIndexList indexList = ism->selectedIndexes();

    DetailedDialog detailedDialog(indexList.at(1).data().toString(),
                                  indexList.at(2).data().toString(),
                                  indexList.at(3).data().toString(),
                                  this);
    detailedDialog.exec();
}

void MainWindow::on_reset_pushButton_clicked()
{
    ui->types_comboBox->setCurrentIndex(0);
    ui->season_comboBox->setCurrentIndex(0);
    ui->contry_comboBox->setCurrentIndex(0);
    ui->vegetarian_pushButton->setChecked(false);
}

void MainWindow::on_types_comboBox_currentIndexChanged(int index)
{
    applyFilter(TYPES_FILTER, index);
}

void MainWindow::on_season_comboBox_currentIndexChanged(int index)
{
    applyFilter(SEASON_FILTER, index);
}

void MainWindow::on_contry_comboBox_currentIndexChanged(int index)
{
    applyFilter(CONTRY_FILTER, index);
}

void MainWindow::on_vegetarian_pushButton_toggled(bool checked)
{
    applyFilter(VEGETARIAN_FILTER, (checked) ? 1 : 0);
}

void MainWindow::on_favorite_pushButton_clicked(bool checked)
{
    if (checked)
    {
        QSqlQuery query;
        query.exec(QString("SELECT fav_id_1, fav_id_2, fav_id_3 FROM users WHERE name = '%1'")
                   .arg(userName));

        if (query.next())
        {
            QString id_filter_string = QString("( %1, %2, %3 )")
                    .arg(query.value(0).toString())
                    .arg(query.value(1).toString())
                    .arg(query.value(2).toString());
            filterClass.applyNew(ID_FILTER,id_filter_string);
        }
        else
            qDebug() << "wrong bd querry result in on_favorite_pushButton_clicked(...) for " << userName;
    }
    else
    {
        filterClass.resetFilter(ID_FILTER);
    }
    model->setFilter(filterClass.currentFilter());
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    applyFilter(DURATION_FILTER, arg1);
}

void MainWindow::on_random_pushButton_clicked()
{
    on_reset_pushButton_clicked();
}

void MainWindow::on_register_pushButton_clicked()
{

}
