#include "cli.h"

CLI::CLI(int &argc, char *argv[], QObject *parent) : QObject(parent)
{
    // Check argument count
    if (argc != 3) {
        printHelp();
        return;
    }

    // Check if arguments have "--help" switch
    for (int i = 0; i < argc; i++) {
        if (!qstrcmp(argv[i], "--help")) {
            printHelp();
            break;
        }
    }

    // If not, make callsign check
    doLookup(QString(argv[2]));
}

void CLI::printHelp() {
    QTextStream(stdout) << "ituprefix - tool for checking callsign country\n"
                        << "Usage: ituprefix [--no-gui CALLSIGN]\n";
}

void CLI::doLookup(QString callsign) {
    // Create object
    Lookup lookupObj(this);

    // Load file
    if (!lookupObj.loadFile()) {
        QTextStream(stderr) << "Could not load prefix list file!";
        return;
    }

    // Perform search
    TEntriesList sResult = lookupObj.searchByCallsign(callsign);

    // Output stream
    QTextStream output(stdout);

    // Print result
    for (auto it = sResult.begin(); it != sResult.end(); it++) {
        output << it->first.first + "-" + it->first.second << "\t\t"
               << it->second << "\n";
    }
}
