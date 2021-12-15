#include "../headers/folderdialog.h"
#include "ui_folderdialog.h"

FolderDialog::FolderDialog(QWidget *parent) : QDialog(parent), ui(new Ui::FolderDialog) {
    ui->setupUi(this);
    //  this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags (this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

FolderDialog::~FolderDialog() {
    delete ui;
}

void FolderDialog::on_buttonBox_accepted() {
    emit sendData(ui->lineEditFolder->text());
}

