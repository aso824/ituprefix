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

    // QTableWidget disabled editing
    ui->tblResults->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblResults->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblResults->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Connect search box signals
    connect(ui->edQuery, SIGNAL(textChanged(QString)), this, SLOT(doSearch()));
}

MainWindow::~MainWindow()
{
    delete lookup;
    delete ui;
}

void MainWindow::doSearch() {
    // Get text to search
    QString query = ui->edQuery->text();

    // Clear table for results
    ui->tblResults->clearContents();
    ui->tblResults->setRowCount(0);

    // Return if search should't executed
    if (query.isEmpty())
        return;

    // Allocate memory for search result
    TEntriesList result;

    // Selecting proper function
    if (ui->cbSearchType->currentIndex() == 0) {
        // Search by callsign
        result = lookup->searchByCallsign(query);
    } else {
        // Search by country
        result = lookup->searchByCountry(query);
    }

    // Fill table
    for (auto it = result.begin(); it != result.end(); it++) {
        // Get current row count
        int row = ui->tblResults->rowCount();

        // Insert new row on end
        ui->tblResults->insertRow(row);

        // Set values on newly added row
        ui->tblResults->setItem(row, 0, new QTableWidgetItem(it->first.first));
        ui->tblResults->setItem(row, 1, new QTableWidgetItem(it->first.second));
        ui->tblResults->setItem(row, 2, new QTableWidgetItem(it->second));
    }
}
