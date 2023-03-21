#include "reLinkCollectionAEP.h"

#include "FsApplication.h"
#include "reLinkCollectionAEPMain.h"

//************************************************************
int main(int argc, char *argv[])
{
    FsApplication a(argc, argv,FsAppName);

    QCoreApplication::setApplicationName(FsAppName);
    QCoreApplication::setOrganizationName(FsOrganizationName);

#if defined(Q_OS_WIN)
    //Windowsで多重起動禁止の処理
    if (!a.isFirstApp()){
        //起動していたら、引数をメッセージで送信して終わる
        QString ret = a.getOpenFileString();
        if (!ret.isEmpty()){
            a.sendMessage(ret);
        }
       return 0;
   }
#endif
    reLinkCollectionAEPMain w;
    w.show();
    //for MAcOSX &Windows
    QObject::connect(&a,SIGNAL(openFiles(QFileInfoList)),
                     &w,SLOT(appendFileInfoList(QFileInfoList)));

    //windows only
#if defined(Q_OS_WIN)
    a.commandline();
    QObject::connect(&a, SIGNAL(onRecieved(const QString)),
                        &w, SLOT(onRecieved(const QString)));
#endif

    return a.exec();
}
//************************************************************
