#ifndef FOLDERDIALOG_H
#define FOLDERDIALOG_H

#include "globals.h"

namespace Ui {
class FolderDialog;
}

class FolderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FolderDialog(QWidget *parent = nullptr);
    ~FolderDialog();

signals:
    void sendData(QString path);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::FolderDialog *ui;
};

#endif // FOLDERDIALOG_H
