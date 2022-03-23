// TopLevel Window for QHdfView
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mhdf = new MOD11_hdf () ;
    nl = 700 ;
    ns = 1320 ;
    nyears = 20 ;
    xloc = ns / 2 ;
    yloc = nl / 2 ;
    LSTFlag = true ;

    connect (ui->image_widget, SIGNAL(clickedXY(int *)), this, SLOT(newXY (int *))) ;
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

    nyears = mhdf->getStack(this->infile.toLatin1().data()) ;
    ui->image_widget->loadQImage (mhdf->nightdata, ns, nl) ;
    //ui->image_widget->loadQImage (mhdf->stack, ns, nl) ;
    ui->image_widget->loadQImage_alt (mhdf->daydata, ns, nl) ;
    ui->image_widget->update() ;
    this->getProfile (ns/2, nl/2) ;
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

void MainWindow::getProfile (int x, int y) {

    int npix = ns * nl ;
    float *ydata = new float [nyears] ;
    float *ydata_day = new float [nyears];
    for (int i=0; i<nyears; i++){
        ydata[i] = mhdf->stackf[i * npix +  ns * y + x] ;
        ydata_day[i] = mhdf->daystackf[i * npix +  ns * y + x] ;
        qDebug() << ydata[i] << "  " << ydata_day[i];
    }
    ui->plot_widget->setYData(0, ydata, nyears);
    ui->plot_widget->setYData(1, ydata_day, nyears);
}

void MainWindow::newXY (int *xy){
    int x, y ;
    x = xy[0];
    y = xy[1];
    this->getProfile(x,y);
}
