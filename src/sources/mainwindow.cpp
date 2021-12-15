#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "../../libs/simplecrypt.cpp"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
//  this->setWindowFlags(Qt::FramelessWindowHint);
    ui->treeView->header()->setStyleSheet("::section { background-color:#181818;}");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->toolBar->setStyleSheet("QToolTip { color:#f8f8f8; background-color:#181818; border: 0px;}");

    ui->actionAddFolder->setEnabled(false);
    ui->actionAddPassword->setEnabled(false);
    ui->actionDelete->setEnabled(false);

    updateFileTree();
    global = new Globals;
    global->createDirIfNotExist(QApplication::applicationDirPath() + WORKING_DIRECTORY);

    active_path = QApplication::applicationDirPath() +  WORKING_DIRECTORY;
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
    ui->treeView->header()->resizeSection(0, 385);


}

MainWindow::~MainWindow() {
    ui->treeView->model()->~QAbstractItemModel();
    delete ui;

}

void MainWindow::updateUserText() {
    if ((master_password == "") || (key == "")) {

        ui->textBrowser->setText("Please select public key or generate it\n"
                                 "Then, type master password\n"
                                 "#### Later there u will see info about selected file and password, with connected to it\n");
    }
    else {
        if (global->isDir(active_path)) {
            ui->textBrowser->setText("Current directory: " + active_path);
        }
        else if (global->isFile(active_path)) {
            QString password_tmp = global->loadfile(active_path);
            SimpleCrypt crypto(key.toLongLong() + master_password.length() + master_password.mid(0,5).toLatin1().toLongLong());
            password_tmp = crypto.decryptToString(password_tmp);

            if (password_tmp == "")
                password_tmp = "Invalid password or no access";
            ui->textBrowser->setText("Current file:\n" + active_path);
            ui->textBrowser->append("\nPassword:\n" + QString(password_tmp));
        }
    }
}

void MainWindow::updateFileTree() {
    model = new QFileSystemModel;
    model->setRootPath(QApplication::applicationDirPath() +  WORKING_DIRECTORY);
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(model->rootPath()));
}

void MainWindow::on_actionAddPassword_triggered() {
    password_window = new PasswordDialog;
    password_window->show();
    connect(password_window, &PasswordDialog::sendData, this, &MainWindow::addPassword);
    connect(password_window, &PasswordDialog::sendData, password_window, &PasswordDialog::accept);
}

void MainWindow::addPassword(QString filename, QString password) {
    SimpleCrypt crypto(key.toLongLong() + master_password.length() + master_password.mid(0,5).toLatin1().toLongLong());
    password = crypto.encryptToString(password);

    global->createFileIfNotExist(active_path + QString("/") + filename);
    global->dumpFile(active_path + QString("/") + filename, password);

}

void MainWindow::on_actionAddFolder_triggered() {
    folder_window = new FolderDialog;
    folder_window->show();
    connect(folder_window, &FolderDialog::sendData, this, &MainWindow::addFolder);
    connect(folder_window, &FolderDialog::sendData, folder_window, &FolderDialog::accept);
}

void MainWindow::addFolder(QString path) {
  global->createDirIfNotExist(active_path + QString("/") + path);
}

void MainWindow::on_actionMaster_triggered() {
    master_window = new MasterDialog;
    master_window->show();

    connect(master_window, &MasterDialog::sendData, this, &MainWindow::setMasterPassword);
    connect(master_window, &MasterDialog::sendData, master_window, &MasterDialog::accept);
}

void MainWindow::setMasterPassword(QString str) {
    master_password = str;
    updateButtons();
}

void MainWindow::on_actionKeys_triggered() {
    keygen_window = new KeygenDialog;
    keygen_window->show();

    connect(keygen_window, &KeygenDialog::sendData, this, &MainWindow::setKey);
    connect(keygen_window, &KeygenDialog::sendData, keygen_window, &KeygenDialog::accept);
}

void MainWindow::setKey(QString str) {
    key = str;
    updateButtons();
}

void MainWindow::on_actionDelete_triggered() {
    if (global->isDir(active_path))
        global->deleteDir(active_path);
    else if (global->isFile(active_path))
        global->deleteFile(active_path);
}

void MainWindow::updateButtons() {
    if (!ui->actionAddFolder->isEnabled() && master_password != "" && key != "") {
        ui->actionAddFolder->setEnabled(true);
        ui->actionAddPassword->setEnabled(true);
        ui->actionDelete->setEnabled(true);
    }
}

void MainWindow::on_treeView_clicked(const QModelIndex &index) {
    active_path = model->filePath(index);
    if (global->isFile(active_path))
        updateUserText();
}

