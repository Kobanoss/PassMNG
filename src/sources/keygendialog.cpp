#include "../headers/keygendialog.h"
#include "ui_keygendialog.h"

KeygenDialog::KeygenDialog(QWidget *parent): QDialog(parent), ui(new Ui::KeygenDialog) {
    ui->setupUi(this);
//    this->setWindowFlags(Qt::FramelessWindowHint);
}

KeygenDialog::~KeygenDialog() {
    delete ui;
}

void KeygenDialog::on_pushButton_Select_clicked() {
    QString path = QFileDialog::getOpenFileName();
    if(!path.isEmpty()) {
        // TODO: ADD TO DATA
    }
}


void KeygenDialog::on_checkBox_show_stateChanged(int state) {
    state == 0?ui->lineEdit_master->setEchoMode(QLineEdit::Password):ui->lineEdit_master->setEchoMode(QLineEdit::Normal);
    state == 0?ui->lineEdit_repeat->setEchoMode(QLineEdit::Password):ui->lineEdit_repeat->setEchoMode(QLineEdit::Normal);
}

