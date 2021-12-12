#ifndef KEYGENDIALOG_H
#define KEYGENDIALOG_H

#include "globals.h"

namespace Ui {
class KeygenDialog;
}

class KeygenDialog : public QDialog {
  Q_OBJECT

public:
  explicit KeygenDialog(QWidget *parent = nullptr);
  ~KeygenDialog();
private slots:
    void on_pushButton_Select_clicked();

    void on_checkBox_show_stateChanged(int state);

private:
    Ui::KeygenDialog *ui;
};

#endif // KEYGENDIALOG_H
