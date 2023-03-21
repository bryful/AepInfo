#ifndef FSAPPLICATION_H
#define FSAPPLICATION_H


#include <QApplication>
#include <QObject>
#include <QFileOpenEvent>
#include <QFileInfo>
#include <QFileInfoList>
#include <QEvent>
#include <QTimer>
#include <QLocalServer>
#include <QLocalSocket>
#include <QTextCodec>
#include <QProcess>

#include "reLinkCollectionAEPMain.h"
class reLinkCollectionAEPForm;

class FsApplication : public QApplication
{
    Q_OBJECT
public:
    explicit FsApplication(int &argc, char **argv,QString uniqKeyString);

#if defined(Q_OS_WIN)
    //引数を解析してファイルとディレクトリだけを獲得openFilesを送信
    void commandline();

    //引数解析の実態。commandlineから呼び出される
    QFileInfoList getOpenFileList();

    //QStringListでは無くQStringで結果を返す。
    QString getOpenFileString();

    //二重機動確認。起動していなかったらサーバー機動起動。していたら引数をメッセージ送信。
    bool isFirstApp();
    //サーバーへメッセージ送信
    void sendMessage(const QString &text);

#endif

signals:
    //引数が得られた
    void openFiles(QFileInfoList);

#if defined(Q_OS_WIN)
    //クライアントから引数が送られてきた
    void onRecieved(const QString);
#endif

public slots:
#if defined(Q_OS_WIN)
    //クライアントが接続したら送信。onRecievedを送信
    void onAccepted();
#endif

protected:
#if defined(Q_OS_MAC)
    //AppleEventsのOpenFileを得たら
    virtual bool event( QEvent * e );
#endif

private:
    const QString   m_uniqKeyString;
#if defined(Q_OS_WIN)
    QLocalSocket    m_localSocket;
    QLocalServer    m_localServer;
#endif
};


#endif // FSAPPLICATION_H
