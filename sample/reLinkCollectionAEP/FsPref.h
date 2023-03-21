#ifndef FsPref_H
#define FsPref_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QFile>
#include <QDir>
#include <QFont>

#include <QStandardPaths>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QByteArray>
#include <QTextStream>


class FsPref : public QObject
{
    Q_OBJECT
private:
    QString     m_prefPath;
    QString     m_prefName;
    QJsonObject m_jo;
    bool        m_loadError;
public:
    explicit FsPref(QString nm = 0,QObject *parent = 0);

    QString prefPath() { return m_prefPath;}
    QString prefName() { return m_prefName;}
    QString prefFullName() { return m_prefPath +"/" +m_prefName;}
    bool loadError(){return m_loadError;}

    int valueInt(QString key,bool *ok);
    double valueDouble(QString key,bool *ok);
    QString valueString(QString key,bool *ok);
    bool valueBool(QString key,bool *ok);
    QFont valueFont(QString key,bool *ok);
    QPoint valuePoint(QString key,bool *ok);
    QStringList valueStringList(QString key,bool *ok);
    QList<double> valueDoubleList(QString key,bool *ok);
    QList<int> valueIntList(QString key,bool *ok);
    QList<bool> valueBoolList(QString key,bool *ok);
    QSize valueSize(QString key,bool *ok);
    QRect valueRect(QString key,bool *ok);
    bool isUndefined(QString k){ return m_jo[k].isUndefined();}

    QByteArray valueByteArray(QString key,bool *ok);

signals:


public slots:
    void clear();
    void setPrefPath(QString s);
    void setPrefName(QString s);
    void setValueInt(QString key,int v);
    void setValueDouble(QString key,double v);
    void setValueString(QString key,QString v);
    void setValueBool(QString key,bool v);
    void setValueFont(QString key,QFont v);
    void setValueStringList(QString key,QStringList v);
    void setValueDoubleList(QString key,QList<double> v);
    void setValueIntList(QString key,QList<int> v);
    void setValueBoolList(QString key,QList<bool> v);

    void setValuePoint(QString key,QPoint v);
    void setValueSize(QString key,QSize v);
    void setValueRect(QString key,QRect v);

    void setValueByteArray(QString key,QByteArray ba);

    void save();
    void load();
};

#endif // FsPref_H
