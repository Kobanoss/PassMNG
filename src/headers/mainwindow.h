#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "globals.h"
#include "keygendialog.h"
#include "passworddialog.h"
#include "masterdialog.h"
#include "folderdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAddPassword_triggered();

    void on_actionAddFolder_triggered();

    void on_actionMaster_triggered();

    void on_actionDelete_triggered();

    void on_actionKeys_triggered();

    void updateFileTree();

    void on_treeView_clicked(const QModelIndex &index);

    void addPassword(QString filename, QString password);

    void addFolder(QString path);

    void setMasterPassword(QString master_password);

    void setKey(QString key);



private:
    QFileSystemModel *model;
    QString active_path;

    QString master_password = "";
    QString key = "";

    Globals *global;

    MasterDialog *master_window;
    KeygenDialog *keygen_window;
    PasswordDialog *password_window;
    FolderDialog *folder_window;

    void updateButtons();
    void updateUserText();

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
