#include "../headers/masterdialog.h"
#include "ui_masterdialog.h"

// Constructor
MasterDialog::MasterDialog(QWidget *parent) : QDialog(parent), ui(new Ui::MasterDialog) {
    ui->setupUi(this);
    // Disable '?' button
    this->setWindowFlags (this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

// Destructor
MasterDialog::~MasterDialog() {
    delete ui;
}

// Change type of lineEdit to show or hide the password
void MasterDialog::on_checkBox_show_stateChanged(int state) {
    state == 0?ui->lineEdit_master->setEchoMode(QLineEdit::Password):ui->lineEdit_master->setEchoMode(QLineEdit::Normal);
    state == 0?ui->lineEdit_repeat->setEchoMode(QLineEdit::Password):ui->lineEdit_repeat->setEchoMode(QLineEdit::Normal);
}

// Send master password to Main window if it possible
void MasterDialog::on_buttonBox_accepted() {
    if ((ui->lineEdit_master->text() == "") || (ui->lineEdit_master->text() != ui->lineEdit_repeat->text())) {
        ui->textBrowser->setText("Invalid master password");
        return;
    }
    else {
        master_password = ui->lineEdit_master->text();
        ui->textBrowser->setText("Master password loaded\n Press OK to continue\n");
    }

    emit sendData(QCryptographicHash::hash(master_password.toUtf8(), QCryptographicHash::Md5).toHex());
}

