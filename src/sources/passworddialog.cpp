#include "../headers/passworddialog.h"
#include "ui_passworddialog.h"

PasswordDialog::PasswordDialog(QWidget *parent): QDialog(parent), ui(new Ui::PasswordDialog) {
  ui->setupUi(this);
//  this->setWindowFlags(Qt::FramelessWindowHint);
}

PasswordDialog::~PasswordDialog() {
    delete ui;
}

void PasswordDialog::generatePassword() {
//TODO

// "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890~!@#$%^&*()_-+={}[]|:;<>,.?" - ALL CHARS
// "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" - Only Alphabetical
// "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890" - Alphabetical and Numerical
}

void PasswordDialog::on_checkBoxShow_stateChanged(int state) {
    state == 0?ui->lineEditPassword->setEchoMode(QLineEdit::Password):ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
}


void PasswordDialog::on_createPasswordButton_clicked() {
    generatePassword();
}
