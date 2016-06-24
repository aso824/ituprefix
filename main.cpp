#include <QApplication>
#include <QCoreApplication>
#include <QTextStream>

#include "cli.h"
#include "mainwindow.h"

QCoreApplication* createApplication(int &argc, char *argv[]) {
    // Iterate over argv[] to find arguments
    for (int i = 1; i < argc; i++)
        if (!qstrcmp(argv[i], "--no-gui") || !qstrcmp(argv[i], "--help"))
            return new QCoreApplication(argc, argv);
    return new QApplication(argc, argv);
}

int main(int argc, char *argv[])
{
    QScopedPointer<QCoreApplication> app(createApplication(argc, argv));

    if (qobject_cast<QApplication*>(app.data())) {
        // GUI version
        MainWindow w;
        w.show();

        return app->exec();
    } else {
        // Non-GUI version
        QScopedPointer<CLI> console(new CLI(argc, argv, app.data()));
        return 0;
    }
}
