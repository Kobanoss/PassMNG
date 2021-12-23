#include "../headers/passworddialog.h"
#include "ui_passworddialog.h"

// Constructor
PasswordDialog::PasswordDialog(QWidget *parent): QDialog(parent), ui(new Ui::PasswordDialog) {
  ui->setupUi(this);
    // Disable '?' button
  this->setWindowFlags (this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

  global = new Globals;
}

// Destructor
PasswordDialog::~PasswordDialog() {
    delete ui;
}

// Generating new strong password with selected parameters
void PasswordDialog::generatePassword() {
    if (ui->passwordTemplateSwitch->currentText() == "All Characters")
        ui->lineEditPassword->setText(global->getRandomString("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890~!@#$%^&*()_-+={}[]|:;<>,.?", ui->spinBox_pwdLength->value()));

    else if (ui->passwordTemplateSwitch->currentText() == "Alphabetical")
        ui->lineEditPassword->setText(global->getRandomString("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", ui->spinBox_pwdLength->value()));

    else if (ui->passwordTemplateSwitch->currentText() == "Alphanumerical")
        ui->lineEditPassword->setText(global->getRandomString("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890", ui->spinBox_pwdLength->value()));
}

// Change type of lineEdit to show or hide the password
void PasswordDialog::on_checkBoxShow_stateChanged(int state) {
    state == 0?ui->lineEditPassword->setEchoMode(QLineEdit::Password):ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
}

// Action on clicking button "Generate"
void PasswordDialog::on_createPasswordButton_clicked() {
    generatePassword();
}

// Send data to Main window if possible
void PasswordDialog::on_buttonBox_accepted() {
    password = ui->lineEditPassword->text();
    if ((password != "") && (ui->lineEditName->text() != "")) {
        emit sendData(ui->lineEditName->text(), password);
    }
}

