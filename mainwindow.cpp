#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mhdf = new MOD11_hdf () ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    this->infile = QFileDialog::getOpenFileName (this, "Open HDF4 File", "/Users/hg1/data") ;
    QFile *qf = new QFile (this->infile) ;
    if (!qf->exists()){
        qDebug() << ("Uhoh") ;
        return ;
    }

    mhdf->openHDF(this->infile.toLatin1().data()) ;
    ui->image_widget->loadQImage (mhdf->nightdata, 1320, 700) ;
    ui->image_widget->loadQImage_alt (mhdf->daydata, 1320, 700) ;
    ui->image_widget->update() ;
    mhdf->getStack(this->infile.toLatin1().data()) ;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit() ;
}

void MainWindow::on_nightButton_toggled(bool checked)
{
    // check if night or day has been selected
    ui->image_widget->setNightFlag (checked) ;
}
