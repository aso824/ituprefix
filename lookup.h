#ifndef LOOKUP_H
#define LOOKUP_H

#include <QObject>
#include <QVector>
#include <QPair>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

typedef QPair<QPair<QString, QString>, QString> TEntry;
typedef QVector<TEntry> TEntriesList;

class Lookup : public QObject
{
        Q_OBJECT
    public:
        explicit Lookup(QObject *parent = 0);
        ~Lookup();
        bool loadFile(QString path = "prefixlist.csv");
        TEntriesList* getList();
        TEntriesList searchByCallsign(QString callsign);
        TEntriesList searchByCountry(QString country);

    protected:
        TEntriesList *entriesList;

};

#endif // LOOKUP_H
