#include <QApplication>
#include <QCoreApplication>
#include <QTextStream>

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

    } else {
        // Non-GUI version

    }

    return app->exec();
}
