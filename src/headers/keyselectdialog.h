#ifndef KEYSELECTDIALOG_H
#define KEYSELECTDIALOG_H

#include <QWidget>

namespace Ui {
class keyselectdialog;
}

class keyselectdialog : public QWidget
{
    Q_OBJECT

public:
    explicit keyselectdialog(QWidget *parent = nullptr);
    ~keyselectdialog();

private:
    Ui::keyselectdialog *ui;
};

#endif // KEYSELECTDIALOG_H
