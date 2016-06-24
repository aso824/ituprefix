#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // QTableWidget first two columns fixed width
    ui->tblResults->setColumnWidth(0, 50);
    ui->tblResults->setColumnWidth(1, 50);

    // QTableWidget last column auto-resizing
    ui->tblResults->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
