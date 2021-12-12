#ifndef TYPEMASTER_H
#define TYPEMASTER_H

#include "globals.h"

namespace Ui {
class TypeMaster;
}

class TypeMaster : public QDialog {
    Q_OBJECT

public:
    explicit TypeMaster(QWidget *parent = nullptr);
    ~TypeMaster();

private slots:
    void on_checkBox_show_stateChanged(int state);

private:
    Ui::TypeMaster *ui;
};

#endif // TYPEMASTER_H
