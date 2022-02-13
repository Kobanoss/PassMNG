#include "../headers/keygendialog.h"
#include "ui_keygendialog.h"

// Constructor
KeygenDialog::KeygenDialog(QWidget *parent): QDialog(parent), ui(new Ui::KeygenDialog) {
    ui->setupUi(this);
    // Disable '?' button
    this->setWindowFlags (this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    global = new Globals;
}

// Destructor
KeygenDialog::~KeygenDialog() {
    delete ui;
}

// Choosing file with filemanager
void KeygenDialog::on_pushButton_Select_clicked() {
    QString path = QFileDialog::getOpenFileName();
    if(!path.isEmpty()) {
        key = global->loadfile(path);
        ui->textBrowser->setText("Key loaded\n Press OK to continue\n\nKey:\n" + key);
    }
    else
        ui->textBrowser->setText("Key not found");
}

// Generating new key and store it ti file
void KeygenDialog::on_pushButton_Genarate_clicked() {
    if ((ui->lineEdit_passphrase->text() == "") || (ui->lineEdit_passphrase->text() != ui->lineEdit_repeat->text())) {
        ui->textBrowser->setText("Invalid passphrase");
        return;
    }

    QString passphrase = ui->lineEdit_passphrase->text();

    passphrase = global->saltData(passphrase, global->getRandomIntString());
    key = QCryptographicHash::hash(passphrase.toUtf8(), QCryptographicHash::Md5).toHex();

    qDebug() << key << passphrase;

    global->createFileIfNotExist(QApplication::applicationDirPath() + WORKING_DIRECTORY + QString("/key.pub"));
    global->dumpFile(QApplication::applicationDirPath() + WORKING_DIRECTORY + QString("/key.pub"), key);

    ui->textBrowser->setText("Key created\nPress OK to continue\n\nKey:\n" + key);
}

// Change type of lineEdit to show or hide the password
void KeygenDialog::on_checkBox_show_stateChanged(int state) {
    state == 0?ui->lineEdit_passphrase->setEchoMode(QLineEdit::Password):ui->lineEdit_passphrase->setEchoMode(QLineEdit::Normal);
    state == 0?ui->lineEdit_repeat->setEchoMode(QLineEdit::Password):ui->lineEdit_repeat->setEchoMode(QLineEdit::Normal);
}

// Sending signal to Main window with key
void KeygenDialog::on_buttonBox_accepted() {
    if (key!= "")
        emit sendData(key);
}


