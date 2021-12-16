#ifndef MASTERDIALOG_H
#define MASTERDIALOG_H

#include "globals.h"

namespace Ui {
class MasterDialog;
}

// Class to implement dialog with selecting master password
// All func realisation in .cpp
class MasterDialog : public QDialog {
    Q_OBJECT

public:
    explicit MasterDialog(QWidget *parent = nullptr);
    ~MasterDialog();

private slots:
    void on_checkBox_show_stateChanged(int state);

    void on_buttonBox_accepted();

signals:
    void sendData(QString master_password);
private:
    QString master_password;

    Ui::MasterDialog *ui;
};

#endif // MASTERDIALOG_H
