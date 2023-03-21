#include "AepFile.h"

//---------------------------------------------------------
AepFile::AepFile(QObject *parent) : QObject(parent)
{
    init();
}
//---------------------------------------------------------
AepFile::AepFile(QString path,QObject *parent): QObject(parent)
{
    load(path);
}

//---------------------------------------------------------
void AepFile::init()
{
    m_buf.clear();
    m_fullpath = "";
}

//---------------------------------------------------------
void AepFile::load(QString path)
{
    init();
    QFile f(path);
    QFileInfo fi(f);
    //あるか？
    if (f.exists() == false) {
        mes("[" + fi.fileName() +"]"+ NS(" ファイルなし!"));
        return;
    }
    //サイズがある程度あるか
    if (fi.size()<1024) {
        mes("[" + fi.fileName() +"]"+ NS(" ロードサイズエラー"));
        return;
    }
    QString ext = fi.suffix().toLower();
    //拡張子の確認
    if (ext!="aep") {
        mes("[" + fi.fileName() +"]"+ NS(" 拡張子エラー!"));
        return;
}
    if (f.open(QIODevice::ReadOnly))
    {
        //読み込み配列の準備
        char *buf = new char[fi.size()];
        QDataStream in(&f);
        int r = in.readRawData(buf,fi.size());
        f.close();
        if(r==fi.size()) {
            m_buf = QByteArray(buf,fi.size());
            if (m_buf.indexOf("RIFX")==0) {
                m_fullpath = fi.absoluteFilePath();
            }else{
                mes("[" + fi.fileName() +"]"+ NS("AEPヘッダーエラー"));
            }

        }else{
            mes("[" + fi.fileName() +"]"+ NS("ロードエラー"));
        }
        delete buf;
    }else{
        mes("[" + fi.fileName() +"]"+ NS("ファイルオープンエラー"));
    }
}
//---------------------------------------------------------
void AepFile::save()
{
    QFileInfo fi(m_fullpath);

    if (m_buf.size()<1024) {
        init();
        mes("[" + fi.fileName() +"]"+ NS("セーブサイズエラー"));
        return;
    }
    QFile f(m_fullpath);
    if( f.exists() == true){
        QString bakFile = m_fullpath+".bak";
        QFile fbak(bakFile);
        if(fbak.exists()==false) {
            QFile::rename(m_fullpath,bakFile);
        }
    }
    char *data = new char[m_buf.size()];
    for (int i=0;i<m_buf.size();i++) data[i] = m_buf[i];
    if (f.open(QIODevice::WriteOnly)){
        if (f.write(data,m_buf.size())==m_buf.size()) {
            mes("[" + fi.fileName() +"]"+ NS("セーブOK!"));
        }else{
            mes("[" + fi.fileName() +"]"+ NS("セーブエラー"));
        }
        f.close();
    }else{
        mes("[" + fi.fileName() +"]"+ NS("セーブオープンエラー"));

    }
    delete data;
}
//---------------------------------------------------------
int AepFile::findChar( char c,int st )
{
    int ret = -1;
    int sz = m_buf.size();
    if (sz<=st) return ret;
    for (int i=st;i<sz ;i++){
        char v = m_buf[i];
        if (c == v) {
            ret = i;
            break;
        }
    }
    return ret;
}
//---------------------------------------------------------
int AepFile::findYen(int st )
{
    int ret = -1;
    int sz = m_buf.size();
    if (sz<=st) return ret;
    for (int i=st;i<sz ;i++){
        char v = m_buf[i];
        if ((v == '\\')||(v=='/')) {
            ret = i;
            break;
        }
    }
    return ret;
}
//---------------------------------------------------------
void AepFile::exec(QString path)
{
    mes("/*-----------------------------------------*/");
    load(path);
    if (m_buf.size()<1024) {
        init();
        return;
    }
    //aepの横に収集フッテージがあるか？
    QString ftgDir = "";

    QDir d1(FsP::getParentPath(m_fullpath)+"/" + footageFolder1);
    if (d1.exists()){
        ftgDir = footageFolder1;
    }else{
        QDir d2(FsP::getParentPath(m_fullpath)+"/" + footageFolder2);
        if (d2.exists()){
            ftgDir = footageFolder2;
        }
    }
    if (ftgDir.isEmpty()) {
        mes("[" + FsP::getFileName(m_fullpath)  +"]"+ NS("収集フォルダ(Footage)がない"));
        init();
        return;
    }
    m_count = 0;
    m_countFixed = 0;
    int pos = 0;
    while (pos>=0) {
        pos = footageExec(pos,ftgDir);
    }
    mes(QString("(%1/%2)Footages fixed!").arg(m_countFixed).arg(m_count));
    save();
}
//---------------------------------------------------------
int AepFile::footageExec(int p,QString ftgF)
{
    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    int ret = -1;

    int v = m_buf.indexOf("Alasalas",p);
    if (v<0) return ret;
    //一応見つけたから返り値を変更
    m_count++;
    ret = p+8;
    //パスを獲得
    int idx1 = v+26;
    int idx2 = findZero(idx1);
    if (idx2<0) return ret;

    QString path= "";
    for (int i=idx1; i<idx2;i++) {
        path += m_buf[i];
    }
    if ((path.size()<=0)||(path.size()>260)) return ret;
    int r = path.indexOf(ftgF);
    if (r<=0) return ret;
    char h = m_buf[idx2+1];
    if(h == 0x02) {
        m_buf[idx2+1] = 0x01;
        m_buf[idx2+2] = (unsigned char)(r-1);
        mes("<"+path+"> " + tr("path fixed!"));
        m_countFixed++;
    }
    ret = idx2+2;
    return ret;

}
