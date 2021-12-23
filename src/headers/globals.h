#ifndef GLOBALS_H
#define GLOBALS_H

// Global imports (needed for most .cpp files)
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
#include <QCryptographicHash>

// Global defines (needed for most .cpp files)
#define WORKING_DIRECTORY_PARENTLESS QString("./PassMNG")
#define WORKING_DIRECTORY_NAME QString("PassMNG")
#define WORKING_DIRECTORY QString("/PassMNG")


// Global class, that provides some functions, which are necessary without reference to another classes
class Globals {

   public:
    // is object with current path is directory?
    bool isFile(QString path) {
        return QFileInfo(path).isFile();
    }

    // is object with current path is file?
    bool isDir(QString path) {
        return QFileInfo(path).isDir();
    }

    // creating directory(including all parents) with path to it, if not exist
    void createDirIfNotExist(QString path) {
        if (!QDir(path).exists())
            QDir().mkpath(path);
    }

    // creating file(including all parents) with path to it, if not exist
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

    // Read file and get data from it in QString format
    QString loadfile(QString filename) {
        QString data;
        QFile file(filename);

        if ((file.exists())&&(file.open(QFile::ReadOnly)))
            data = QTextStream(&file).readAll();

        file.close();
        return data;
    }

    // Write to file some data in QString format
    void dumpFile(QString filename, QString data) {
        QFile file(filename);

        if ((file.exists())&&(file.open(QFile::WriteOnly)))
            file.write(data.toUtf8());
        file.close();
    }

    // Mixing data with salt
    QString saltData(QString salt, QString data) {
        data = salt + data;
        for (int i = 0; i < salt.length(); i++) {
            data += salt;
        }
        return data;
    }

    // Getting random QString, which contains only numbers
    QString getRandomIntString() const {
       const QString possibleCharacters("0123456789");
       const int randomStringLength = 64;

       QString randomString;
       for(int i=0; i<randomStringLength; ++i) {
           int index = qrand() % possibleCharacters.length();
           QChar nextChar = possibleCharacters.at(index);
           randomString.append(nextChar);
       }
       return randomString;
    }

    // Getting random QString, which selected symbols and size
    QString getRandomString(const QString possibleCharacters, const int randomStringLength) const {
       QString randomString;
       for(int i=0; i<randomStringLength; ++i) {
           int index = qrand() % possibleCharacters.length();
           QChar nextChar = possibleCharacters.at(index);
           randomString.append(nextChar);
       }
       return randomString;
    }

    // Getting random in [lowest,highest]
    int getRandomInt(int lowest, int highest ){
        QRandomGenerator rand_obj;
        rand_obj.seed((long double)clock());
        return (highest-lowest > 0)?rand_obj.bounded(highest - lowest) + lowest:0;
    }

    // Deleting file, if exist
    void deleteFile(QString filename) {
        if (QFile(filename).exists())
            QFile(filename).remove();
    }

    // Deleting directory(and all childs) with path
    void deleteDir(QString path) {
        if (QDir(path).exists())
            QDir(path).removeRecursively();
    }

};



#endif // GLOBALS_H
