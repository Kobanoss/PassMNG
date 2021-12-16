#include "../headers/folderdialog.h"
#include "ui_folderdialog.h"

// Constructor
FolderDialog::FolderDialog(QWidget *parent) : QDialog(parent), ui(new Ui::FolderDialog) {
    ui->setupUi(this);
    // Disable '?' button
    this->setWindowFlags (this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

// Destructor
FolderDialog::~FolderDialog() {
    delete ui;
}

// Sending signal to Main window with foldername(or path)
void FolderDialog::on_buttonBox_accepted() {
    emit sendData(ui->lineEditFolder->text());
}

