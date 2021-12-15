#include "../headers/masterdialog.h"
#include "ui_masterdialog.h"

MasterDialog::MasterDialog(QWidget *parent) : QDialog(parent), ui(new Ui::MasterDialog) {
    ui->setupUi(this);
//    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags (this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

MasterDialog::~MasterDialog() {
    delete ui;
}


void MasterDialog::on_checkBox_show_stateChanged(int state) {
    state == 0?ui->lineEdit_master->setEchoMode(QLineEdit::Password):ui->lineEdit_master->setEchoMode(QLineEdit::Normal);
    state == 0?ui->lineEdit_repeat->setEchoMode(QLineEdit::Password):ui->lineEdit_repeat->setEchoMode(QLineEdit::Normal);
}


void MasterDialog::on_buttonBox_accepted() {
    if ((ui->lineEdit_master->text() == "") || (ui->lineEdit_master->text() != ui->lineEdit_repeat->text())) {
        ui->textBrowser->setText("Invalid master password");
        return;
    }
    else {
        master_password = ui->lineEdit_master->text();
        ui->textBrowser->setText("Master password loaded\n Press OK to continue\n");
    }

    emit sendData(master_password);
}

