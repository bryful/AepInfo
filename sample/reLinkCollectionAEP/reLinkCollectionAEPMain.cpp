#include "reLinkCollectionAEPMain.h"

//***************************************************************************
reLinkCollectionAEPMain::reLinkCollectionAEPMain(QWidget *parent) :
    QMainWindow(parent)
{

    //ドラッグ＆ドロップを許可
    this->setAcceptDrops(true);
    this->setWindowTitle(FsAppName);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    m_settings = new reLinkCollectionAEPettings;


    lbCaption = new QLabel(NS("リンク切れした収集済みAEPをここへドラッグ"));
    lbCaption->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    edFilePath = new QTextEdit;
    edFilePath->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    edFilePath->setReadOnly(true);


    QVBoxLayout *vl = new QVBoxLayout;
    vl->addWidget(lbCaption);
    vl->addWidget(edFilePath);

    QWidget *cw = new QWidget;
    cw->setLayout(vl);
    this->setCentralWidget(cw);

    m_settings->load(this);

    aep = new AepFile;
    connect(aep,SIGNAL(mes(QString)),this,SLOT(addMes(QString)));

    setWindowTitle(tr("re-link Collection Files for After Effects Project File"));

}
//*******************************
void reLinkCollectionAEPMain::about()
{
    QMessageBox::about(this, FsAppName,
             NS("リンク切れした収集済みAEPを何とかします（成功率50%）"));

}
//*******************************
void reLinkCollectionAEPMain::createActions()
{
    //----------------------
    quitAct = new QAction(QIcon(":/res/Quit.png"), tr("Q&uit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("close"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

    //----------------------
    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    //----------------------
    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    /*
    connect(edFilePath, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
    connect(edFilePath, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));
    */
}
//*******************************
void reLinkCollectionAEPMain::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(quitAct);


    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}
//*******************************
void reLinkCollectionAEPMain::createToolBars()
{
}
//*******************************
void reLinkCollectionAEPMain::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));

}

//***************************************************************************
void reLinkCollectionAEPMain::closeEvent(QCloseEvent *)
{
    m_settings->save(this);
}
//***************************************************************************
void reLinkCollectionAEPMain::appendFileInfoList( const QFileInfoList &info_list)
{
    QFileInfoList fl;
    foreach( const QFileInfo &info, info_list )
    {
       aep->exec(info.absoluteFilePath());
    }

}
//***************************************************************************
#if defined(Q_OS_WIN)
void reLinkCollectionAEPMain::onRecieved(const QString str)
{

    QFileInfoList fl;
    if (!str.isEmpty()) {
        QStringList list = str.split(";");
        if (list.size()>1){
            //メッセージで送られてくる引数の最初の１個はアプリ自体のパス。
            for (int i=1; i<list.size();i++)
            {
                aep->exec(list[i]);
            }
            statusBar()->showMessage(tr("Finished"));
        }
    }
}
#endif
//*******************************************************************************
// ドラッグ＆ドロップを許可する
void reLinkCollectionAEPMain::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasFormat("text/uri-list")){
        e->acceptProposedAction();
    }
}
//*******************************************************************************
// ドラッグ＆ドロップの処理
void reLinkCollectionAEPMain::dropEvent(QDropEvent *e)
{
    QFileInfoList fl;
    QList <QUrl> urls = e->mimeData()->urls();
    if (urls.isEmpty()) return;
    for (int i=0; i<urls.size();i++){
        QFileInfo fi(urls[i].toLocalFile());
        aep->exec(fi.absoluteFilePath());
    }
    statusBar()->showMessage(tr("Finished"));

}
//***************************************************************************
void reLinkCollectionAEPMain::addMes(QString s)
{
    QString p = edFilePath->toPlainText();
    if (p.isEmpty()==false) p += "\r\n";
    p += s;
    edFilePath->setPlainText(p );
    edFilePath->update();
}
