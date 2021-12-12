#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
//  this->setWindowFlags(Qt::FramelessWindowHint);
    ui->treeView->header()->setStyleSheet("::section { background-color:#181818;}");

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QApplication::applicationFilePath());
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(model->rootPath()));

    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
    ui->treeView->header()->resizeSection(0, 385);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_actionAddPassword_triggered() {
    password_window = new PasswordDialog;
    password_window->show();
}


void MainWindow::on_actionAddFolder_triggered() {

}


void MainWindow::on_actionMaster_triggered() {
    master_window = new TypeMaster;
    master_window->show();
}


void MainWindow::on_actionDelete_triggered() {

}


void MainWindow::on_actionKeys_triggered() {
    keygen_window = new KeygenDialog;
    keygen_window->show();
}

