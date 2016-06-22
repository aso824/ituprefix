#include "lookup.h"

Lookup::Lookup(QObject *parent) : QObject(parent)
{
    // Initialize vector
    entriesList = new TEntriesList;
}

Lookup::~Lookup() {
    delete entriesList;
}

bool Lookup::loadFile(QString path) {
    // Open file
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    // Read file line by line
    QTextStream in(&file);
    while(!in.atEnd()) {
        // Read current line
        QString line = in.readLine();
        QStringList cells = line.split(",");
        TEntry tmp;
        tmp.first.first = cells[0];
        tmp.first.second = cells[1];
        tmp.second = cells[2];

        // Add to vector
        entriesList->push_back(tmp);
    }

    // Close file
    file.close();

    return true;
}

TEntriesList *Lookup::getList() {
    return entriesList;
}

TEntriesList Lookup::searchByCallsign(QString callsign) {
    // Trim string
    if (callsign.length() > 3)
        callsign = callsign.left(3);

    // Remove number
    int trPos = callsign.lastIndexOf(QRegularExpression("\\d"));
    callsign = callsign.left(trPos);

    // Convert to upper case
    callsign = callsign.toUpper();

    // Create result object
    TEntriesList result;

    // Iterate over list
    for (auto it = entriesList->begin(); it != entriesList->end(); it++) {
        QString delimiterA = it->first.first,
                delimiterB = it->first.second;

        // Trim if required
        int csLen = callsign.length();
        if (csLen < 3) {
            delimiterA = delimiterA.left(csLen);
            delimiterB = delimiterB.left(csLen);
        }

        // Compare strings
        if (callsign.compare(delimiterA) >= 0 && callsign.compare(delimiterB) <= 0)
            result.push_back(*it);
    }

    return result;
}

TEntriesList Lookup::searchByCountry(QString country) {
    // Normalize string
    country = country.toLower();

    // Create result object
    TEntriesList result;

    // Iterate over list
    for (auto it = entriesList->begin(); it != entriesList->end(); it++) {
        int pos = 0;
        while((pos = it->second.toLower().indexOf(country, pos)) != -1) {
            result.push_back(*it);
            pos++;
        }
    }

    return result;
}
