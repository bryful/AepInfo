#include "FsPref.h"

//***************************************************
FsPref::FsPref(QString nm,QObject *parent) :
    QObject(parent)
{
    setPrefPath("");
    if (nm.isEmpty()){
        m_prefName = "app.pref";
    }else{
        setPrefName(nm);
    }
    m_loadError = true;
}
//***************************************************
void FsPref::clear()
{
    m_loadError = true;
    QStringList keys = m_jo.keys();
    if (keys.size()>0){
        for (int i=0; i<keys.size();i++){
            m_jo.remove(keys[i]);
        }
    }
}
//*****************************************************
void FsPref::setPrefName(QString s)
{
    s =s.trimmed();

    if (s.isEmpty()) {
        m_prefName = "";
    }else{
        int idx = s.lastIndexOf("/");
        s = s.mid(idx+1);
        idx = s.lastIndexOf(".");
        if (idx<0) {
            s += ".pref";
        }
        m_prefName = s;
    }

}
//***************************************************
void FsPref::setPrefPath(QString s)
{
    QDir d(s);
    if ((!s.isEmpty())&&(d.exists())){
        m_prefPath = d.absolutePath();
    }else{
        m_prefPath = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);
    }
}

//***************************************************
void FsPref::save()
{
    QJsonDocument jd(m_jo);
    QByteArray js = jd.toJson();

    QFile f(prefFullName());
    if (f.open(QFile::WriteOnly)){
        QTextStream out(&f);
        out.setCodec("UTF-8");
        out << js;
        f.close();
    }
}

//***************************************************
void FsPref::load()
{

    m_loadError = true;
    clear();

    QFile f(prefFullName());
    if ( f.exists()==false) return;
    QByteArray js = "";
    if (! f.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    js = f.readAll();
    f.close();

    if (js.isEmpty() ) return;
    QJsonDocument jd = QJsonDocument::fromJson(js);
    if ( (js.isEmpty())||(js.isNull())) return;

    m_jo = jd.object();
    m_loadError = false;

}

//***************************************************
int FsPref::valueInt(QString key,bool *ok)
{
    int ret;
    *ok = false;
    if (! m_jo[key].isUndefined()){
        if(m_jo[key].isDouble()){
            ret =(int)m_jo[key].toDouble();
            *ok = true;
        }
    }
    return ret;
}

//***************************************************
void FsPref::setValueInt(QString key,int v)
{
    m_jo[key] = (double)v;
}
//***************************************************
double FsPref::valueDouble(QString key,bool *ok)
{
    double ret;
    *ok = false;
    if (! m_jo[key].isUndefined()){
        if(m_jo[key].isDouble()){
            ret = m_jo[key].toDouble();
            *ok = true;
        }
    }
    return ret;
}

//***************************************************
void FsPref::setValueDouble(QString key,double v)
{
    m_jo[key] = v;
}
//***************************************************
void FsPref::setValuePoint(QString key,QPoint v)
{
    QJsonArray ja;
    ja.append(QJsonValue((double)v.x()));
    ja.append(QJsonValue((double)v.y()));
    m_jo[key] = ja;

}
//***************************************************
QPoint FsPref::valuePoint(QString key,bool *ok)
{
    QPoint ret;
    *ok = false;
    if (! m_jo[key].isUndefined()){
        if(m_jo[key].isArray()){
            QJsonArray ja = m_jo[key].toArray();
            if (ja.size()>=2){
                if ( (ja[0].isDouble())&&(ja[1].isDouble())){
                    ret.setX((int)ja[0].toDouble());
                    ret.setY((int)ja[1].toDouble());
                    *ok = true;
                }
            }
        }
    }
    return ret;
}
//***************************************************
void FsPref::setValueSize(QString key,QSize v)
{
    QJsonArray ja;
    ja.append(QJsonValue((double)v.width()));
    ja.append(QJsonValue((double)v.height()));
    m_jo[key] = ja;

}
//***************************************************
QSize FsPref::valueSize(QString key,bool *ok)
{
    QSize ret;
    *ok = false;
    if (! m_jo[key].isUndefined()){
        if(m_jo[key].isArray()){
            QJsonArray ja = m_jo[key].toArray();
            if (ja.size()>=2){
                if ( (ja[0].isDouble())&&(ja[1].isDouble())){
                    ret.setWidth((int)ja[0].toDouble());
                    ret.setHeight((int)ja[1].toDouble());
                    *ok = true;
                }
            }
        }
    }
    return ret;
}

//***************************************************
void FsPref::setValueRect(QString key,QRect v)
{
    QJsonArray ja;
    ja.append(QJsonValue((double)v.left()));
    ja.append(QJsonValue((double)v.top()));
    ja.append(QJsonValue((double)v.width()));
    ja.append(QJsonValue((double)v.height()));
    m_jo[key] = ja;

}
//***************************************************
QRect FsPref::valueRect(QString key,bool *ok)
{
    QRect ret(0,0,0,0);
    *ok = false;
    if (! m_jo[key].isUndefined()){
        if(m_jo[key].isArray()){
            QJsonArray ja = m_jo[key].toArray();
            if (ja.size()>=4){
                if ( (ja[0].isDouble())&&(ja[1].isDouble())&&(ja[2].isDouble())&&(ja[3].isDouble())){
                    ret.setLeft((int)ja[0].toDouble());
                    ret.setTop((int)ja[1].toDouble());
                    ret.setWidth((int)ja[2].toDouble());
                    ret.setHeight((int)ja[3].toDouble());
                    *ok = true;
                }
            }
        }
    }
    return ret;
}
//***************************************************
void FsPref::setValueString(QString key,QString v)
{
    m_jo[key] = v;

}
//***************************************************
QString FsPref::valueString(QString key,bool *ok)
{
    QString ret;
    *ok = false;
    if (! m_jo[key].isUndefined()){
        if(m_jo[key].isString()){
            ret = m_jo[key].toString();
            *ok = true;
        }
    }
    return ret;
}
//***************************************************
void FsPref::setValueByteArray(QString key,QByteArray ba)
{
    QString s = "";
    if (ba.size()){
        for (int i=0; i<ba.size();i++){
            QString ss;
            ss.setNum((unsigned char)ba[i],16);

            if (ss.size()==0){
                ss = "00";
            }else if (ss.size()==1) {
                ss = "0" + ss;
            }

            s += ss;
        }
    }
    m_jo[key] = s;
}
//***************************************************
void FsPref::setValueBool(QString key,bool v)
{
    m_jo[key] = v;

}
//***************************************************
bool FsPref::valueBool(QString key,bool *ok)
{
    bool ret;
     *ok = false;
    if (! m_jo[key].isUndefined()){
        if(m_jo[key].isBool()){
            ret = m_jo[key].toBool();
            *ok = true;
        }
    }
    return ret;
}
//***************************************************
void FsPref::setValueFont(QString key,QFont v)
{
    m_jo[key] = v.toString();

}
//***************************************************
QFont FsPref::valueFont(QString key,bool *ok)
{
    QFont ret;
    *ok = false;
    if (! m_jo[key].isUndefined()){
        if(m_jo[key].isString()){
            ret.fromString(m_jo[key].toString());
            *ok = true;
        }
    }
    return ret;
}
//***************************************************
void FsPref::setValueStringList(QString key,QStringList v)
{
    QJsonArray ja;
    if(v.size()>0){
        for ( int i=0; i<v.size();i++){
            ja.append(v[i]);
        }
    }
    m_jo[key] = ja;
}
//***************************************************
QStringList FsPref::valueStringList(QString key,bool *ok)
{
    QStringList ret;
    *ok = false;
    if (! m_jo[key].isUndefined()){
        if(m_jo[key].isArray()){
            QJsonArray ja = m_jo[key].toArray();
            if(ja.size()>0){
                for (int i=0; i<ja.size();i++){
                    if(ja[i].isString()){
                        ret.append(ja[i].toString());
                    }
                }
            }
            *ok = true;
        }
    }
    return ret;
}
//***************************************************
void FsPref::setValueDoubleList(QString key,QList<double> v)
{
    QJsonArray ja;
    if(v.size()>0){
        for ( int i=0; i<v.size();i++){
            ja.append((double)v[i]);
        }
    }
    m_jo[key] = ja;
}
//***************************************************
QList<double> FsPref::valueDoubleList(QString key,bool *ok)
{
    QList<double> ret;
    *ok = false;
    if (! m_jo[key].isUndefined()){
        if(m_jo[key].isArray()){
            QJsonArray ja = m_jo[key].toArray();
            if(ja.size()>0){
                for (int i=0; i<ja.size();i++){
                    if(ja[i].isDouble()){
                        ret.append(ja[i].toDouble());
                    }
                }
            }
            *ok = true;
        }
    }
    return ret;
}
//***************************************************
void FsPref::setValueIntList(QString key,QList<int> v)
{
    QJsonArray ja;
    if(v.size()>0){
        for ( int i=0; i<v.size();i++){
            ja.append((double)v[i]);
        }
    }
    m_jo[key] = ja;
}
//***************************************************
QList<int> FsPref::valueIntList(QString key,bool *ok)
{
    QList<int> ret;
    *ok = false;
    if (! m_jo[key].isUndefined()){
        if(m_jo[key].isArray()){
            QJsonArray ja = m_jo[key].toArray();
            if(ja.size()>0){
                for (int i=0; i<ja.size();i++){
                    if(ja[i].isDouble()){
                        ret.append((int)ja[i].toDouble());
                    }
                }
            }
            *ok = true;
        }
    }
    return ret;
}
//***************************************************
void FsPref::setValueBoolList(QString key,QList<bool> v)
{
    QJsonArray ja;
    if(v.size()>0){
        for ( int i=0; i<v.size();i++){
            ja.append((bool)v[i]);
        }
    }
    m_jo[key] = ja;
}
//***************************************************
QList<bool> FsPref::valueBoolList(QString key,bool *ok)
{
    QList<bool> ret;
    *ok = false;
    if (! m_jo[key].isUndefined()){
        if(m_jo[key].isArray()){
            QJsonArray ja = m_jo[key].toArray();
            if(ja.size()>0){
                for (int i=0; i<ja.size();i++){
                    if(ja[i].isBool()){
                        ret.append(ja[i].toBool());
                    }
                }
            }
            *ok = true;
        }
    }
    return ret;
}
//***************************************************
QByteArray FsPref::valueByteArray(QString key,bool *ok)
{
    QByteArray ret;
    *ok = false;
    if (!m_jo[key].isUndefined()){
        if(m_jo[key].isString()){
            QString s = m_jo[key].toString();
            int cnt = s.size() /2;
            if(cnt>=1){
                for (int i=0; i<cnt;i++){
                    int n = s.mid(i*2,2).toInt(0,16);
                    ret += (unsigned char)n;
                }
                *ok = true;
            }
        }
    }
    return ret;
}

//***************************************************
