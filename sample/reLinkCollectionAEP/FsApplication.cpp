#include "FsApplication.h"

//************************************************************
FsApplication::FsApplication(int &argc, char **argv,QString uniqKeyString) :
  m_uniqKeyString(uniqKeyString)
  ,QApplication( argc, argv)
{
#if defined(Q_OS_WIN)
    connect(&m_localServer,SIGNAL(newConnection()),this,SLOT(onAccepted()));
#endif
}
//************************************************************
#if defined(Q_OS_MAC)
bool FsApplication::event( QEvent * e )
{
   if( e->type() == QEvent::FileOpen ){
       const QFileOpenEvent * const file_event = static_cast<QFileOpenEvent *>(e);
       QFileInfoList info_list;
       const QString file = file_event->file();
       info_list.push_back( file );
       openFiles(info_list);
       return true;
   }
   return QApplication::event(e);
}
#endif
//************************************************************
#if defined(Q_OS_WIN)
bool FsApplication::isFirstApp()
{
    m_localSocket.connectToServer(m_uniqKeyString);
    if (m_localSocket.waitForConnected(200))
    {
        return false;
    }else{
        m_localServer.listen(m_uniqKeyString);
        return true;
    }
}
#endif
//************************************************************
#if defined(Q_OS_WIN)
void FsApplication::onAccepted()
{
    QLocalSocket *sock = m_localServer.nextPendingConnection();
    while (sock->bytesAvailable() < (int)sizeof(quint32))
        sock->waitForReadyRead();

    QByteArray ba = sock->readAll();
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString buff = codec->toUnicode(ba);
    emit onRecieved(buff);
    delete sock;
}
#endif
//************************************************************
#if defined(Q_OS_WIN)
void FsApplication::sendMessage(const QString &text)
{
    m_localSocket.write(text.toUtf8());
    m_localSocket.flush();
    if (m_localSocket.waitForBytesWritten(1000))
    {
        return;
    }

    return;
}
#endif

//************************************************************
#if defined(Q_OS_WIN)
QFileInfoList FsApplication::getOpenFileList()
{
    const QStringList argv = arguments();
    QFileInfoList file_list;
    if (argv.size()>1){
        for( int i = 1; i < argv.size(); ++i )
        {
          const QFileInfo finfo( argv.at(i) );
          if( finfo.exists() )
          {
            file_list.push_back( argv.at(i) );
          }
        }
    }
    return file_list;
}
#endif
//************************************************************
#if defined(Q_OS_WIN)
//返す引数の１個目はアプリのパス。
QString FsApplication::getOpenFileString()
{
    const QStringList argv = arguments();
    QString ret = "";
    if (argv.size()>0){
        for( int i = 0; i < argv.size(); ++i )
        {
          const QFileInfo finfo( argv.at(i) );
          if( finfo.exists() )
          {
              if (!ret.isEmpty()) ret += ";";
              ret += finfo.absoluteFilePath();
          }
        }
    }
    return ret;
}
#endif

//************************************************************
#if defined(Q_OS_WIN)
void FsApplication::commandline()
{
    QFileInfoList file_list = getOpenFileList();

    if(file_list.size()>0){
        openFiles(file_list);
    }
}
#endif
//************************************************************
