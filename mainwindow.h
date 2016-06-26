#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>

#include "lookup.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void showAboutAuthor();
        void showAboutQt();

    private:
        Ui::MainWindow *ui;
        Lookup* lookup;

    private slots:
        void doSearch();
};

#endif // MAINWINDOW_H
