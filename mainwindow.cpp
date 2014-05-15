#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "detaileddialog.h"
#include "registrationform.h"
#include <QMessageBox>
#include <QtSql/QSqlRelation>
#include <QtSql/QSqlQuery>
#include <QModelIndexList>
#include <QModelIndex>
#include <QDesktopServices>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("app.db");
    if (!db.open())
    {
        QMessageBox::critical(this, tr("Database error"), tr("Can't open database"));
        return;
    }
    statusBar()->showMessage(tr("Database opened"), 5000);

    prepareModel();

    on_logout_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    on_logout_pushButton_clicked();
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
    query.exec(QString("SELECT role, favorites FROM users WHERE name = '%1' AND pass = '%2'")
               .arg(userName)
               .arg(pass));

    if (query.next())
    {
        switch (query.value(0).toInt())
        {
        case ADMINISTRATOR_ROLE:
            adminLogin();
            break;
        case USER_ROLE:
            break;
        default:
            qDebug() << "wrong role for user " << userName;
        }
        favorites.init(query.value(1).toString());
        ui->favorite_pushButton->setEnabled(true);
        ui->login_stackedWidget->setCurrentIndex(1);
        ui->userName_label->setText(tr("Welcome, ") + userName + "!");
    }
    else
        QMessageBox::information(this, tr("Login incorrect"), tr("Login name or password is incorrect"));
}

void MainWindow::adminLogin()
{
    isAdminLoggedIn = true;
    ui->add_pushButton->setVisible(true);
    ui->del_pushButton->setVisible(true);
    ui->save_pushButton->setVisible(true);
    ui->pucancel_shButton->setVisible(true);
    ui->main_tableView->setEditTriggers(QAbstractItemView::EditKeyPressed | QAbstractItemView::SelectedClicked
                                        | QAbstractItemView::AnyKeyPressed);
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
    case ID_FILTER:
        filterClass.applyNew(ID_FILTER, favorites.asSqlSet());
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

    model->select();
    ui->main_tableView->setItemDelegate(new QSqlRelationalDelegate(ui->main_tableView));
    ui->main_tableView->hideColumn(0);
    ui->main_tableView->hideColumn(8);
    ui->main_tableView->hideColumn(9);

    ui->main_tableView->setColumnWidth(0,20);
    ui->main_tableView->setColumnWidth(1,200);
    ui->main_tableView->setColumnWidth(2,220);
    ui->main_tableView->setColumnWidth(3,220);
    ui->main_tableView->setColumnWidth(4,120);
    ui->main_tableView->setColumnWidth(5,80);
    ui->main_tableView->setColumnWidth(6,80);
    ui->main_tableView->setColumnWidth(7,100);
    ui->main_tableView->setColumnWidth(8,30);
    ui->main_tableView->setColumnWidth(9,60);

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
    ui->favorite_pushButton->setDisabled(true);
    isAdminLoggedIn = false;
    ui->add_pushButton->setVisible(false);
    ui->del_pushButton->setVisible(false);
    ui->save_pushButton->setVisible(false);
    ui->pucancel_shButton->setVisible(false);
    ui->main_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    if (userName.isEmpty())
        return;
    QSqlQuery query;
    query.exec(QString("UPDATE users SET favorites = '%1' WHERE name = '%2'")
               .arg(favorites.asString())
               .arg(userName));
    userName.clear();
}

void MainWindow::on_main_tableView_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index)

    QItemSelectionModel * ism = ui->main_tableView->selectionModel();
    QModelIndexList indexList = ism->selectedIndexes();
    int id = indexList.at(0).data().toInt();
    QByteArray pic = indexList.at(8).data().toByteArray();
    QPixmap pixmap;
    if (!pic.isEmpty())
        pixmap.loadFromData(pic);
    DetailedDialog detailedDialog(id,
                                  indexList.at(1).data().toString(),
                                  indexList.at(2).data().toString(),
                                  indexList.at(3).data().toString(),
                                  pixmap,
                                  this);
    if (favorites.inFavorites(id))
        detailedDialog.setFavorite();
    if (isAdminLoggedIn)
        detailedDialog.allowEdit();
    connect(&detailedDialog, SIGNAL(addingFavorite(int)), &favorites, SLOT(add(int)));
    connect(&detailedDialog, SIGNAL(remFavorite(int)), &favorites, SLOT(remove(int)));
    detailedDialog.exec();
    if (isAdminLoggedIn)
    {
        QString name;
        QString consist;
        QString description;
        QString imageFormat;
        detailedDialog.getData(id, name, consist, description, pixmap, imageFormat);
        QByteArray byteArray;
        if (detailedDialog.imageWasUpdated())
        {
            QBuffer buffer(&byteArray);
            buffer.open(QIODevice::WriteOnly);
            pixmap.save(&buffer, imageFormat.toUpper().toLocal8Bit());
            model->setData(indexList.at(8),byteArray);
        }

        model->setData(indexList.at(1),name);
        model->setData(indexList.at(2),consist);
        model->setData(indexList.at(3),description);
        on_save_pushButton_clicked();
    }
    if (ui->favorite_pushButton->isChecked())
        applyFilter(ID_FILTER, 1);
}

void MainWindow::on_reset_pushButton_clicked()
{
    ui->types_comboBox->setCurrentIndex(0);
    ui->season_comboBox->setCurrentIndex(0);
    ui->contry_comboBox->setCurrentIndex(0);
    ui->spinBox->setValue(0);
    ui->vegetarian_pushButton->setChecked(false);
    model->setFilter("");
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
    applyFilter(ID_FILTER, (checked) ? 1 : 0);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    applyFilter(DURATION_FILTER, arg1);
}

void MainWindow::on_random_pushButton_clicked()
{
    on_reset_pushButton_clicked();
    QStringList randId;
    QSqlQuery query(QString("SELECT * FROM (SELECT id FROM bluda WHERE (bluda.type = 1 OR bluda.type = 0) ORDER BY RANDOM() LIMIT 1)") +
                    QString(" UNION ALL ") +
                    QString("SELECT * FROM (SELECT id FROM bluda WHERE (bluda.type = 2 OR bluda.type = 0) ORDER BY RANDOM() LIMIT 1)") +
                    QString(" UNION ALL ") +
                    QString("SELECT * FROM (SELECT id FROM bluda WHERE (bluda.type = 3 OR bluda.type = 0) ORDER BY RANDOM() LIMIT 1)"));
    while (query.next())
        randId.append(query.value(0).toString());
    model->setFilter(QString("bluda.id IN ( ") + randId.join(", ") + QString(" )"));
}

void MainWindow::on_register_pushButton_clicked()
{
    RegistrationForm regForm(this);
    if (QDialog::Accepted == regForm.exec())
    {
        QString newUserName = regForm.getUsername();
        QString pass = regForm.getPassword();
        QSqlQuery query(QString("INSERT INTO users (name, pass) VALUES ('%1', '%2')")
                        .arg(newUserName)
                        .arg(pass));
        if ((query.lastError().type() != QSqlError::NoError))
        {
            QMessageBox::warning(this, tr("Adding new user error"),
                                 tr("There is an error during adding new user. Try another username or connect to your administrator"));
            return;
        }
        ui->login_lineEdit->setText(newUserName);
        ui->password_lineEdit->setText(pass);
        on_login_pushButton_clicked();
    }
}

void MainWindow::on_about_triggered()
{
    QMessageBox::about(this, tr("About QtCookBook"), tr("This program created by Mariya Tsviga"));
}

void MainWindow::on_main_tableView_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos)
}

void MainWindow::on_add_pushButton_clicked()
{
    model->insertRow(model->rowCount());
}

void MainWindow::on_del_pushButton_clicked()
{
    QModelIndexList index = ui->main_tableView->selectionModel()->selectedIndexes();

    if (!index.isEmpty())
    {
        int row = index.at(0).row();
        model->removeRow(row);
        ui->main_tableView->setRowHidden(row, true);
        model->submitAll();
    }
}

void MainWindow::on_save_pushButton_clicked()
{
    model->submitAll();
}

void MainWindow::on_pucancel_shButton_clicked()
{
    model->revertAll();
    model->select();
}

void MainWindow::on_help_triggered()
{
    QDesktopServices::openUrl(QUrl("help.pdf"));
}

void MainWindow::on_password_lineEdit_returnPressed()
{
    on_login_pushButton_clicked();
}

void MainWindow::on_login_lineEdit_returnPressed()
{
    on_login_pushButton_clicked();
}
