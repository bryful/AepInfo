#ifndef FSSKELTONSETTINGS_H
#define FSSKELTONSETTINGS_H

/*
 * アプリ固有設定を管理する
 *
 */


#include "reLinkCollectionAEP.h"

#include "FsApplication.h"
#include "FsPref.h"
#include "FsP.h"

#include "reLinkCollectionAEPMain.h"

#define PREF_GEO        "geometry"
#define PREF_STA        "status"

#define PREF_FILEPATH   "filePath"

class FsPref;
class reLinkCollectionAEPMain;

class reLinkCollectionAEPettings : public QObject
{
    Q_OBJECT
public:
    explicit reLinkCollectionAEPettings(QObject *parent = 0);

signals:

public slots:
    void assign(reLinkCollectionAEPettings *m); //アプリ固有の設定を複写
    void save(reLinkCollectionAEPMain *form); //設定の保存
    void load(reLinkCollectionAEPMain *form);



private:
    FsPref      *m_pref;
    //アプリ固有の情報
};

#endif // FSSKELTONSETTINGS_H
