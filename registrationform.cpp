#include "registrationform.h"
#include "ui_registrationform.h"
#include <QMessageBox>

RegistrationForm::RegistrationForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

QString RegistrationForm::getUsername()
{
    return ui->userName_lineEdit->text();
}

QString RegistrationForm::getPassword()
{
    return ui->pass_lineEdit->text();
}

void RegistrationForm::on_buttonBox_accepted()
{
    if (ui->pass_lineEdit->text() != ui->passRepeat_lineEdit->text())
        QMessageBox::information(this, tr("Password error"), tr("Passwords doesn't match"));
    else if (ui->userName_lineEdit->text().size() <= 1)
        QMessageBox::information(this, tr("Wrong username"), tr("Username must be more than 1 character"));
    else if (ui->pass_lineEdit->text().size() <= 4)
        QMessageBox::information(this, tr("Incorrect password"), tr("Password must be more than 4 character"));
    else
        accept();
}
