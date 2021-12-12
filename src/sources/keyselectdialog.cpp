#include "../headers/keyselectdialog.h"
#include "ui_keyselectdialog.h"

keyselectdialog::keyselectdialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::keyselectdialog)
{
    ui->setupUi(this);
}

keyselectdialog::~keyselectdialog()
{
    delete ui;
}
