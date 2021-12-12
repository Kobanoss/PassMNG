#include "../headers/typemaster.h"
#include "ui_typemaster.h"

TypeMaster::TypeMaster(QWidget *parent) : QDialog(parent), ui(new Ui::TypeMaster) {
    ui->setupUi(this);
//    this->setWindowFlags(Qt::FramelessWindowHint);
}

TypeMaster::~TypeMaster() {
    delete ui;
}

void TypeMaster::on_checkBox_show_stateChanged(int state) {
    state == 0?ui->lineEdit_master->setEchoMode(QLineEdit::Password):ui->lineEdit_master->setEchoMode(QLineEdit::Normal);
    state == 0?ui->lineEdit_repeat->setEchoMode(QLineEdit::Password):ui->lineEdit_repeat->setEchoMode(QLineEdit::Normal);
}

