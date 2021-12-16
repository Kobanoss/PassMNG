#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include "globals.h"

namespace Ui {
class PasswordDialog;
}

// Class to implement dialog with creating file and password to it
// All func realisation in .cpp
class PasswordDialog : public QDialog {
  Q_OBJECT

public:
  explicit PasswordDialog(QWidget *parent = nullptr);
  ~PasswordDialog();

private slots:
    void on_checkBoxShow_stateChanged(int state);

    void on_createPasswordButton_clicked();

    void on_buttonBox_accepted();

signals:
    void sendData(QString filename, QString password);

private:
    QString password;

    void generatePassword();

    Globals *global;
    Ui::PasswordDialog *ui;
};

#endif // PASSWORDDIALOG_H
