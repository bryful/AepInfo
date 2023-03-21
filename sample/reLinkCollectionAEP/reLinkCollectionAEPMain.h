#ifndef FSSKELTONMAIN_H
#define FSSKELTONMAIN_H


#include "reLinkCollectionAEP.h"

#include "FsApplication.h"
#include "FsPref.h"
#include "FsP.h"

#include "reLinkCollectionAEPettings.h"

#include "AepFile.h"

class reLinkCollectionAEPettings;

#define NS(s) QString::fromLocal8Bit(s)


class reLinkCollectionAEPMain : public QMainWindow
{
    Q_OBJECT
public:
    explicit reLinkCollectionAEPMain(QWidget *parent = 0);

signals:

public slots:
    void appendFileInfoList( const QFileInfoList &info_list);
#if defined(Q_OS_WIN)
    //クライアントから送信された。コマンドライン・アイコンへのドラッグ&ドロップ
    void onRecieved(const QString str);
#endif

    void about();

private:
    AepFile *aep;

    QString m_filePath;
    //サンプル用
    QTextEdit *edFilePath;
    QLabel *lbCaption;

    reLinkCollectionAEPettings *m_settings;


    QMenu       *fileMenu;
    QMenu       *editMenu;
    QMenu       *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();


    //File
    QAction *quitAct;

    //help
    QAction *aboutAct;
    QAction *aboutQtAct;


protected:
    //フォームへのドラッグ&ドロップ
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    //終了時の処理
    void closeEvent(QCloseEvent *);

public slots:
    void addMes(QString s);

};

#endif // FSSKELTONMAIN_H
