#ifndef AEPFILE_H
#define AEPFILE_H
#include <QDebug>

#include <QObject>
#include <QApplication>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextCodec>
#include <QTextStream>
#include <QClipboard>
#include <QByteArray>
#include <QDataStream>

#include "FsP.h"

#define footageFolder1 "(Footage)"
#define footageFolder2 QString::fromLocal8Bit("(フッテージ)")
#define NS(s) QString::fromLocal8Bit(s)

//Alasalas
class AepFile : public QObject
{
    Q_OBJECT
public:
    explicit AepFile(QObject *parent = 0);
    explicit AepFile(QString path,QObject *parent = 0);

    qint64 size() { return m_buf.size();}
    bool isEnabled() { return (m_buf.size()>0);}
private:
    QByteArray m_buf;
    QString m_fullpath;
    int findChar(char c, int st = 0);
    int findZero(int st = 0) { return findChar('\0',st);}
    int findYen(int st);
    int findFootage(int st = 0) { return m_buf.indexOf("Alasalas",st);}

    int m_count;
    int m_countFixed;
signals:
    void mes(QString);
public slots:
    void init();
    void load(QString path);
    void save();
    void exec(QString path);
    int footageExec(int p,QString ftgF);
private slots:
};

#endif // AEPFILE_H
