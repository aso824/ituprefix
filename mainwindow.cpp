#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Prepare Lookup class object
    lookup = new Lookup(this);

    // Load data file
    if (!lookup->loadFile()) {
        QMessageBox::critical(this, tr("ITU prefix lookup"),
                              tr("Could not open prefixlist.csv\n"
                                 "Did you run update.py script?"),
                              QMessageBox::Ok);
        QTimer::singleShot(0, this, SLOT(close()));
    }

    // QTableWidget first two columns fixed width
    ui->tblResults->setColumnWidth(0, 50);
    ui->tblResults->setColumnWidth(1, 50);

    // QTableWidget last column auto-resizing
    ui->tblResults->horizontalHeader()->setStretchLastSection(true);

    // Connect search box signals
    connect(ui->edQuery, SIGNAL(textChanged(QString)), this, SLOT(doSearch()));
}

MainWindow::~MainWindow()
{
    delete lookup;
    delete ui;
}

void MainWindow::doSearch() {

}
