#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include "globals.h"

namespace Ui {
class PasswordDialog;
}

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
    void generatePassword();

    Globals *global;
    Ui::PasswordDialog *ui;
};

#endif // PASSWORDDIALOG_H
