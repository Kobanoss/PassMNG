#ifndef GLOBALS_H
#define GLOBALS_H

#include <QDialog>
#include <QCloseEvent>
#include <QMainWindow>
#include <QFileSystemModel>
#include "deselectabletreeview.h"
#include <QHeaderView>
#include <QFileDialog>
#include <QScopedPointer>
#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QRandomGenerator>
#include <time.h>

#define WORKING_DIRECTORY_PARENTLESS QString("./PassMNG")
#define WORKING_DIRECTORY_NAME QString("PassMNG")
#define WORKING_DIRECTORY QString("/PassMNG")


class Globals {

   public:
    bool isFile(QString path) {
        return QFileInfo(path).isFile();
    }

    bool isDir(QString path) {
        return QFileInfo(path).isDir();
    }

    void createDirIfNotExist(QString path) {
        if (!QDir(path).exists())
            QDir().mkpath(path);
    }

    void createFileIfNotExist(QString filename) {
        QFile file(filename);
        QFileInfo file_info(file);
        QDir dir;

        QString file_path = file_info.path();
        dir.mkpath(file_path);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           file.open(QIODevice::WriteOnly);

        file.close();
    }

    QString loadfile(QString filename) {
        QString data;
        QFile file(filename);

        if ((file.exists())&&(file.open(QFile::ReadOnly)))
            data = QTextStream(&file).readAll();

        file.close();
        return data;
    }

    void dumpFile(QString filename, QString data) {
        QFile file(filename);

        if ((file.exists())&&(file.open(QFile::WriteOnly)))
            file.write(data.toUtf8());
        file.close();
    }

    QString saltData(QString salt, QString data) {
        return salt + data;
    }

    QString getRandomIntString() const
    {
       const QString possibleCharacters("0123456789");
       const int randomStringLength = 4;

       QString randomString;
       for(int i=0; i<randomStringLength; ++i)
       {
           int index = qrand() % possibleCharacters.length();
           QChar nextChar = possibleCharacters.at(index);
           randomString.append(nextChar);
       }
       return randomString;
    }

    int getRandomInt(int lowest, int highest){
        QRandomGenerator rand_obj;
        rand_obj.seed((long double)clock());
        return (highest-lowest > 0)?rand_obj.bounded(highest - lowest) + lowest:0;
    }


    void deleteFile(QString filename) {
        if (QFile(filename).exists())
            QFile(filename).remove();
    }

    void deleteDir(QString path) {
        if (QDir(path).exists())
            QDir(path).removeRecursively();
    }

};



#endif // GLOBALS_H
