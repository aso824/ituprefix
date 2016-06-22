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
    doLookup();
}

void CLI::printHelp() {
    QTextStream(stdout) << "ituprefix - tool for checking callsign country\n"
                        << "Usage: ituprefix [--no-gui CALLSIGN]\n";
}

void CLI::doLookup() {


}
