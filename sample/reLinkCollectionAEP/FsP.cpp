#include "FsP.h"

//**********************************************************
FsP::FsP(QString s)
{
    m_path = "";
    m_isRoot = false;
    if ((!s.isNull())&&(!s.isEmpty())){
        setFullPath(s);
    }
}
//**********************************************************
FsP& FsP::operator =(QString s)
{
    m_path = "";
    m_isRoot = false;
    setFullPath(s);
    return *this;
}
//**********************************************************
bool FsP::operator ==(QString s)
{
    return (m_path == s);
}
//**********************************************************
bool FsP::operator ==(FsP s)
{
    return (m_path == s.m_path);

}
//**********************************************************
QString FsP::getFileName(QString s)
{
    QString ret = s;
    if (!ret.isEmpty()){
        int idx = ret.lastIndexOf("/");
        if (idx>=0){
            ret = ret.mid(idx+1);
        }
    }
    return ret;

}
//**********************************************************
QString FsP::getFileNameWithoutExt(QString s)
{
    QString ret = getFileName(s);
    if (!ret.isEmpty()){
        int idx = ret.lastIndexOf(".");
        if (idx>=0){
            ret = ret.left(idx);
        }
    }
    return ret;
}

//**********************************************************
QString FsP::getParentPath(QString s)
{
    QString ret = "";
    if (!s.isEmpty()){
        if (s=="/"){
            ret = "";
        }else{
            int idx = s.lastIndexOf("/");
            if (idx>0){
                ret = s.left(idx);
            }
        }
    }
    return ret;
}

//**********************************************************
QString FsP::getExt(QString s)
{
    QString ret = "";
    if (!s.isEmpty()){
        QString f = getFileName(s);
        int idx = f.lastIndexOf(".");
        if (idx>=0){
            ret = f.mid(idx);
        }
    }
    return ret;

}

//**********************************************************
bool FsP::makeFolder(QString s)
{
    s = QFileInfo(s).absoluteFilePath();
    QStringList sa = s.split("/");
    // C:/Bin/aaa
    // /users/roto/document/aaa
    if (sa.size()<2) return true;
    QString t = sa[0];
    for (int i=1; i<sa.size();i++) {
        t = t + "/" +  sa[i];
        QDir d(t);
        if (!d.exists()) {
            QFileInfo fi(d.absolutePath());
            fi.absoluteDir().mkdir(sa[i]);
        }
    }
    return true;

}
//**********************************************************
QString FsP::fileName()
{
    return getFileName(m_path);
}
//**********************************************************
QString FsP::ext()
{
    return getExt(m_path);
}
//**********************************************************
QString FsP::fileNameWithoutExt()
{
    return getFileNameWithoutExt(m_path);
}
//**********************************************************
QString FsP::parentPath()
{
    return getParentPath(m_path);

}
//**********************************************************
QString FsP::changeExt(QString s,QString ne)
{
    QString ret = s;
    int idxDot = s.lastIndexOf(".");
    if (idxDot>=0){
        int idxSepa = s.lastIndexOf("/");
        if (idxDot>idxSepa){
            if (!ne.isEmpty())if (ne[0]!= '.') ne = "." + ne;
            ret = s.left(idxDot) + ne;
        }
    }
    return ret;
}
//**********************************************************
void FsP::setExt(QString ext)
{
    QString p = "";
    if (!m_path.isEmpty()){
        int idx = m_path.lastIndexOf(".");
        int idx2 = m_path.lastIndexOf("/");
        if ((idx>=0)&&( idx > idx2)) {
            QString e = m_path.mid(idx);
            if ( e == ext) return;
            p = m_path.left(idx);
        }else{
            p = m_path;
        }
    }
    m_path = p + ext;
}
//**********************************************************
void FsP::setFileName(QString s)
{
    QString p = "";
    if (!m_path.isEmpty()){
        int idx = m_path.lastIndexOf("/");
        if (idx>=0) {
            QString f = m_path.mid(idx+1);
            if ( f == s) return;
            p = m_path.left(idx);
        }
    }
    m_path = p + "/" + s;

}

//**********************************************************
void FsP::setFullPath(QString p)
{
    m_isRoot = false;
#if defined(Q_OS_MAC)
#elif defined(Q_OS_WIN)
    p = p.replace("\\","/");
#endif

    int ln = p.length();
    if (ln>1){
        if (p[ln-1] == '/'){
            p = p.left(ln-1);
        }
    }
    if (m_path != p){
        m_path = p;
        if (m_path=="/"){
            m_path = "";
            m_isRoot = true;
        }else{
            ln = m_path.length();
            if (ln==2){
                if (m_path[1]==':'){
                    m_isRoot = true;
                }
            }
        }

    }
}
//**********************************************************
FsP FsP::parent()
{
    FsP ret;
    if (!m_path.isEmpty()){
        if ((m_path != "/")&&(m_path != "./")&&(m_path != "../")){
            int idx = m_path.lastIndexOf("/");
            if (idx>=0) {
                ret = m_path.left(idx);
            }
        }
    }
    return ret;
}

//**********************************************************
bool FsP::exists()
{
    QFileInfo fi(m_path);
    return fi.exists();
}
//**********************************************************
bool FsP::isFile()
{
    QFileInfo fi(m_path);
    return fi.isFile();
}
//**********************************************************
bool FsP::isDir()
{
    QFileInfo fi(m_path);
    return fi.isDir();
}
//**********************************************************
bool FsP::mkDir()
{
    return makeFolder(m_path);
}
//**********************************************************
bool FsP::saveText(QString str)
{
    bool ret = false;
    QFile f(m_path);
    if (f.open(QFile::WriteOnly)){
        QTextStream out(&f);
        out.setCodec("UTF-8");
        out << str;
        f.close();
        ret = true;
    }
    return ret;
}
//**********************************************************
QString FsP::loadText()
{
    QString ret = "";
    QFile f(m_path);
    if ( f.open(QIODevice::ReadOnly | QIODevice::Text)) {
       ret = QString::fromUtf8(f.readAll());
       f.close();
    }
    return ret;
}

//**********************************************************
QString  FsP::combine(QString p, QString n)
{
    QString ret = "";
    if (p.isEmpty()){
        ret = n;
    }else{
        ret = p;
        if (p[p.size()-1]!='/') ret += "/";
        ret += n;
    }
    return ret;
}
//**********************************************************
