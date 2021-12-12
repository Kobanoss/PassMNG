#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "globals.h"
#include "keygendialog.h"
#include "passworddialog.h"
#include "typemaster.h"

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

private:
    TypeMaster *master_window;
    KeygenDialog *keygen_window;
    PasswordDialog *password_window;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
