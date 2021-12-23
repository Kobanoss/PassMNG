#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "../../libs/simplecrypt.cpp"

// Constructor
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // Modify TreeView colors
    ui->treeView->header()->setStyleSheet("::section { background-color:#181818;}");

    // Disable '?' button
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Modify toolbar colors
    ui->toolBar->setStyleSheet("QToolTip { color:#f8f8f8; background-color:#181818; border: 0px;}");

    // Disable part of toolbar buttons until key and MP selected
    ui->actionAddFolder->setEnabled(false);
    ui->actionAddPassword->setEnabled(false);
    ui->actionDelete->setEnabled(false);

    global = new Globals;

    // Creating password manager directory and main folder in it (choose to call it "Data")
    global->createDirIfNotExist(QApplication::applicationDirPath() + WORKING_DIRECTORY);
    global->createDirIfNotExist(QApplication::applicationDirPath() + WORKING_DIRECTORY + "/Data");
    updateFileTree();

    // Set Tree active_path to working directory path
    active_path = QApplication::applicationDirPath() +  WORKING_DIRECTORY;

    // Disable filesize, date and etc.
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
    ui->treeView->header()->resizeSection(0, 385);


}

// Destructor
MainWindow::~MainWindow() {
    ui->treeView->model()->~QAbstractItemModel();
    delete ui;

}

// Updating text in TextBrowser, using selected folder/file data and decrypt if needed
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
            bool ok;
            QString password_tmp = global->loadfile(active_path);
            qDebug() << key << " " << master_password << password_tmp;
            QString seed = QCryptographicHash::hash((key + master_password).toUtf8(), QCryptographicHash::Md5).toHex();
            qDebug() << seed << seed.left(15).toLongLong(&ok, 16) + seed.right(16).toLongLong(&ok, 16);
            SimpleCrypt crypto(seed.left(15).toLongLong(&ok, 16) + seed.right(16).toLongLong(&ok, 16));
            password_tmp = crypto.decryptToString(password_tmp);

            password_tmp = password_tmp.left(password_tmp.length() - key.length() - master_password.length());
            qDebug() << key << " " << master_password << password_tmp;

            if (password_tmp == "")
                password_tmp = "Invalid password or no access";
            ui->textBrowser->setText("Current file:\n" + active_path);
            ui->textBrowser->append("\nPassword:\n" + QString(password_tmp));
        }
    }
}

// Updating Tree (used only once), after that, apdating automaticly
void MainWindow::updateFileTree() {
    model = new QFileSystemModel;
    model->setRootPath(QApplication::applicationDirPath() +  WORKING_DIRECTORY);
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(model->rootPath()));
}

// Action on click to "Add Password" toolbar button
void MainWindow::on_actionAddPassword_triggered() {
    password_window = new PasswordDialog;
    password_window->show();
    connect(password_window, &PasswordDialog::sendData, this, &MainWindow::addPassword);
    connect(password_window, &PasswordDialog::sendData, password_window, &PasswordDialog::accept);
}

// Slot, calling, when get signal from another window
// Creating a file with password
void MainWindow::addPassword(QString filename, QString password) {
    bool ok;
    global->createFileIfNotExist(active_path + QString("/") + filename);
    qDebug() << key << " " << master_password << password << "ADDING";
    QString seed = QCryptographicHash::hash((key + master_password).toUtf8(), QCryptographicHash::Md5).toHex();
    qDebug() << seed << seed.left(15).toLongLong(&ok, 16) << seed.right(16).toLongLong(&ok, 16);
    SimpleCrypt crypto(seed.left(15).toLongLong(&ok, 16) + seed.right(16).toLongLong(&ok, 16));
    password = crypto.encryptToString(password + key + master_password);
    qDebug() << key << " " << master_password << password << "ADDING";
    global->dumpFile(active_path + QString("/") + filename, password);

}

// Action on click to "Add Folder" toolbar button
void MainWindow::on_actionAddFolder_triggered() {
    folder_window = new FolderDialog;
    folder_window->show();
    connect(folder_window, &FolderDialog::sendData, this, &MainWindow::addFolder);
    connect(folder_window, &FolderDialog::sendData, folder_window, &FolderDialog::accept);
}

// Slot, calling, when get signal from another window
// Creating a folder
void MainWindow::addFolder(QString path) {
  global->createDirIfNotExist(active_path + QString("/") + path);
}

// Action on click to "Master password" toolbar button
void MainWindow::on_actionMaster_triggered() {
    master_window = new MasterDialog;
    master_window->show();

    connect(master_window, &MasterDialog::sendData, this, &MainWindow::setMasterPassword);
    connect(master_window, &MasterDialog::sendData, master_window, &MasterDialog::accept);
}

// Slot, calling, when get signal from another window
// Sets the master password
void MainWindow::setMasterPassword(QString str) {
    master_password = str;
    updateButtons();
}

// Action on click to "Select key" toolbar button
void MainWindow::on_actionKeys_triggered() {
    keygen_window = new KeygenDialog;
    keygen_window->show();

    connect(keygen_window, &KeygenDialog::sendData, this, &MainWindow::setKey);
    connect(keygen_window, &KeygenDialog::sendData, keygen_window, &KeygenDialog::accept);
}

// Slot, calling, when get signal from another window
// Sets the Key
void MainWindow::setKey(QString str) {
    key = str;
    updateButtons();
}

// Action on click to "Delete" toolbar button
void MainWindow::on_actionDelete_triggered() {
    if (global->isDir(active_path))
        global->deleteDir(active_path);
    else if (global->isFile(active_path))
        global->deleteFile(active_path);
}

// Function, which makes able to click all buttons on toolbar
void MainWindow::updateButtons() {
    if (!ui->actionAddFolder->isEnabled() && master_password != "" && key != "") {
        ui->actionAddFolder->setEnabled(true);
        ui->actionAddPassword->setEnabled(true);
        ui->actionDelete->setEnabled(true);
    }
}

// Action, when user click or select someting in FileTree
void MainWindow::on_treeView_clicked(const QModelIndex &index) {
    active_path = model->filePath(index);
    if (global->isFile(active_path))
        updateUserText();
}

