#include "reLinkCollectionAEPettings.h"

//*****************************************************
reLinkCollectionAEPettings::reLinkCollectionAEPettings(QObject *parent) :
    QObject(parent)
{
    m_pref = new FsPref(FsAppName);
    QString p = m_pref->prefPath() + "/" +FsAppName ;
    QDir d(p);
    if (!d.exists()) FsP::makeFolder(p);

}
//*****************************************************
void reLinkCollectionAEPettings::assign(reLinkCollectionAEPettings *)
{
}

//*****************************************************
void reLinkCollectionAEPettings::save(reLinkCollectionAEPMain *form)
{
    m_pref->setValueByteArray(PREF_GEO,form->saveGeometry());
    m_pref->setValueByteArray(PREF_STA,form->saveState());
    m_pref->save();
}
//*****************************************************
void reLinkCollectionAEPettings::load(reLinkCollectionAEPMain *form)
{
    m_pref->load();
    if (m_pref->loadError()) {
        return;
    }
    bool ok = false;
    QByteArray ba;
    QString s = "";
    ba = m_pref->valueByteArray(PREF_GEO,&ok);
    if (ok) form->restoreGeometry(ba);
    ba = m_pref->valueByteArray(PREF_STA,&ok);
    if (ok) form->restoreState(ba);
}
//*****************************************************
