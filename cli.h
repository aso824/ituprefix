#ifndef CLI_H
#define CLI_H

#include <QObject>
#include <QTextStream>
#include <QCoreApplication>

#include "lookup.h"

class CLI : public QObject
{
        Q_OBJECT
    public:
        explicit CLI(int &argc, char *argv[], QObject *parent = 0);

    private:
        void printHelp();
        void doLookup(QString callsign);
};

#endif // CLI_H
