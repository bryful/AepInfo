#ifndef FSP_H
#define FSP_H


#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>

class FsP
{
private:
    QString m_path;
    bool    m_isRoot;
public:
    FsP(QString s = 0);

    FsP& operator =(QString s);
    bool operator ==(QString s);
    bool operator ==(FsP s);

    //単独で使えるメソッド
    static QString getFileName(QString s);
    static QString getFileNameWithoutExt(QString s);
    static QString getParentPath(QString s);
    static QString getExt(QString s);
    static QString changeExt(QString s,QString ne);
    static bool makeFolder(QString s);
    static QString combine(QString p, QString n);


    QString fullPath(){ return m_path;}
    QString ext();
    QString fileName();
    QString fileNameWithoutExt();
    QString parentPath();

    FsP parent();

    void setExt(QString ext);
    void setFileName(QString s);
    void setFullPath(QString p);

    bool exists();
    bool isFile();
    bool isDir();
    bool mkDir();
    bool isRoot() {return m_isRoot;}

    bool saveText(QString str);
    QString loadText();

    /*
    QFile file() {
        if (isFile()==true){
            QFile ret(m_path);
            return ret;
        }
        return NULL;
    }
    QFile dir() {
        QDir ret = NULL;
        if (isDir()==true){
            QDir d(m_path);
            return d;
        }
        return NULL;
    }
    */
};

#endif // FSP_H
