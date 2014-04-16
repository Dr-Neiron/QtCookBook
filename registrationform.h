#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QDialog>

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit RegistrationForm(QWidget *parent = 0);
    ~RegistrationForm();
    QString getUsername();
    QString getPassword();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::RegistrationForm *ui;
};

#endif // REGISTRATIONFORM_H
