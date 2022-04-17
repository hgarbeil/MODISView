// TopLevel Window for QHdfView
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mod11_hdf = new MOD11_hdf () ;
    mod13_hdf = new MOD13_hdf () ;
    nl = 700 ;
    ns = 1320 ;
    nyears = 20 ;
    xloc = ns / 2 ;
    yloc = nl / 2 ;
    LSTFlag = true ;
    m11dir = new QString ("/Users/hg1/data/MOD11") ;
    m13dir = new QString ("/Users/hg1/data/MOD13") ;

    connect (ui->image_widget, SIGNAL(clickedXY(int *)), this, SLOT(newXY (int *))) ;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mod11_hdf ;
    delete mod13_hdf ;
}

void MainWindow::on_actionOpen_triggered()
{

    if (LSTFlag){

    this->infile = QFileDialog::getOpenFileName (this, "Open HDF4 File", *m11dir) ;
    QFile *qf = new QFile (this->infile) ;
    if (!qf->exists()){
        qDebug() << ("Uhoh") ;
        return ;
    }

    // if MOD11 is selected
    mod11_hdf->openHDF(this->infile.toLatin1().data()) ;
    nyears = mod11_hdf->getStack(this->infile.toLatin1().data()) ;
    ui->image_widget->loadQImage (mod11_hdf->nightdata, ns, nl) ;
    //ui->image_widget->loadQImage (mod11_hdf->stack, ns, nl) ;
    ui->image_widget->loadQImage_alt (mod11_hdf->daydata, ns, nl) ;
    ui->fnameLabel->setText (mod11_hdf->curfile.c_str()) ;
    } else {
        this->infile = QFileDialog::getOpenFileName (this, "Open HDF4 File", *m13dir) ;
        QFile *qf = new QFile (this->infile) ;
        if (!qf->exists()){
            qDebug() << ("Uhoh") ;
            return ;
        }

        // if MOD11 is selected
        mod13_hdf->openHDF(this->infile.toLatin1().data()) ;
        nyears = mod13_hdf->getStack(this->infile.toLatin1().data()) ;
        ui->image_widget->loadQImage (mod13_hdf->ndvidata, ns, nl) ;
        //ui->image_widget->loadQImage (mod11_hdf->stack, ns, nl) ;
        //ui->image_widget->loadQImage_alt (mod11_hdf->daydata, ns, nl) ;


    }
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
    if (LSTFlag){
        for (int i=0; i<nyears; i++){
            ydata[i] = mod11_hdf->stackf[i * npix +  ns * y + x] ;
            ydata_day[i] = mod11_hdf->daystackf[i * npix +  ns * y + x] ;
            qDebug() << ydata[i] << "  " << ydata_day[i];
        }
    } else {
        for (int i=0; i<nyears; i++){
            ydata[i] = mod13_hdf->stackf[i * npix +  ns * y + x] ;
            //ydata_day[i] = mod13_hdf->daystackf[i * npix +  ns * y + x] ;
            qDebug() << ydata[i] ;
        }

    }
    ui->plot_widget->setYData(0, ydata, nyears);
    if (LSTFlag)
        ui->plot_widget->setYData(1, ydata_day, nyears);
    delete [] ydata ;
    delete [] ydata_day ;

}

void MainWindow::newXY (int *xy){
    int x, y ;
    x = xy[0];
    y = xy[1];
    this->getProfile(x,y);
}


void MainWindow::on_landtempRB_toggled(bool checked)
{
    this->LSTFlag = checked ;


}
