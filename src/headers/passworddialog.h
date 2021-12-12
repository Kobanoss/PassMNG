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

private:
    void generatePassword();
    Ui::PasswordDialog *ui;
};

#endif // PASSWORDDIALOG_H
