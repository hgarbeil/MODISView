#include "myprofileplot.h"
#include <qcustomplot.h>
#include <QVector>
#include <QToolTip>
#include <QMenu>


MyProfilePlot::MyProfilePlot(QWidget *parent) :
    QCustomPlot(parent)
{

    nprofiles = 2 ;
    nptsProfile = 480;
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    addGraph();
    addGraph();

    graph(0)->setData(x, y);
    // give the axes some labels:
    xAxis->setLabel("Pixel");
    yAxis->setLabel("DN");
    // set axes ranges, so we see all data:
    xAxis->setRange(0,nptsProfile);
    yAxis->setRange(0, 20000);
    //vline = new QCPItemLine (this) ;
    //vline->start->setCoords (QPointF(104.,0.)) ;
    //vline->end->setCoords(QPointF(104, 14000)) ;
    this->axisRect()->setBackground (Qt::gray) ;

    //this->legend->setVisible(true) ;
    replot() ;


     rescaleFlag = false ;
    colorPlots = new QColor [12] ;
    colorPlots[0]= QColor(Qt::blue) ;
    colorPlots[1] = QColor(Qt::red) ;
    colorPlots[2] = QColor(Qt::magenta) ;
    colorPlots[3] = QColor(Qt::white) ;
    //colorPlots[4] =  QColor::setRgb(127,127,0) ;
    colorPlots[4] = QColor(Qt::cyan) ;
    colorPlots[5] = QColor(Qt::yellow) ;
    colorPlots[6] = QColor(Qt::blue) ;
    colorPlots[7] = QColor(Qt::magenta) ;
    //colorPlots[4] =  QColor::setRgb(127,127,0) ;
    colorPlots[8] =  QColor(Qt::magenta) ;
    colorPlots[9] = QColor(Qt::yellow) ;
    colorPlots[10] = QColor(Qt::white) ;

    QPen pen (Qt::red) ;
    graph(0)->setPen (pen) ;
    graph(0)->setName ("hot") ;
    QPen penblue (Qt::blue) ;
    graph(1)->setPen (penblue) ;
    graph(1)->setName ("cold") ;

    setInteraction(QCP::iRangeZoom, true) ;
    setContextMenuPolicy(Qt::CustomContextMenu) ;
    connect (this, SIGNAL(customContextMenuRequested(const QPoint &)),
             this, SLOT(ShowContextMenu(const QPoint&))) ;


}

MyProfilePlot::~MyProfilePlot(){
    delete [] colorPlots ;
}

void MyProfilePlot::setNumberOfPlots (int nplots){
    int i ;
    if (nplots > nprofiles){
        for (i=nprofiles; i<nplots; i++){
            this->addGraph() ;
            graph(i)->setPen (QPen(colorPlots[i])) ;
        }

    }
    nprofiles = nplots ;

}

void MyProfilePlot::displayLegend(bool b){
    this->legend->setVisible (b) ;
}

void MyProfilePlot::setXYData (float *x, float *y, int npts){

    int i ;
    xdata.clear() ;
    ydata.clear () ;

    for (i=0; i<npts; i++){
        xdata.append(x[i]) ;
        ydata.append(y[i]) ;
    }
    graph(0)->setData(xdata, ydata) ;

    //yAxis->rescale (true) ;
    rescaleAxes() ;
    this->replot() ;
}

void MyProfilePlot::setXYData2 (float *x, float *y, int npts){

    int i ;
    xdata.clear() ;
    ydata.clear () ;

    for (i=0; i<npts; i++){
        xdata.append(x[i]) ;
        ydata.append(y[i]) ;
    }
    graph(1)->setData(xdata, ydata) ;

    //yAxis->rescale (true) ;
    //rescaleAxes() ;
    this->replot() ;
}

void MyProfilePlot::setXYData (int graphnum, float *x, float *y, int npts){

    int i ;
    xdata.clear() ;
    ydata.clear () ;
    //this->clearGraphs() ;
    //this->clearItems() ;
    //this->addGraph() ;

    for (i=0; i<npts; i++){
        xdata.append(x[i]) ;
        ydata.append(y[i]) ;
    }

    graph(graphnum)->setData(xdata, ydata) ;

    //yAxis->rescale (true) ;
    rescaleAxes() ;
    this->replot() ;
}

void MyProfilePlot::plotMany (float *x, float *y, int npts, int nplots, int span){

    int i, ip ;
    float maxVal = -1E6 ;


    this->clearGraphs() ;
    this->clearItems() ;

    for (ip=0; ip<nplots; ip++){
        xdata.clear() ;
        ydata.clear () ;

        this->addGraph() ;

        for (i=0; i<npts; i++){
            xdata.append(x[i]) ;
            ydata.append(y[i+ip*span]) ;
            if (y[i+ip*span]>maxVal) maxVal = y[i+ip*span] ;
        }



        graph(ip)->setData(xdata, ydata) ;
        graph(ip)->setPen (QPen(colorPlots[ip])) ;
    }
    xAxis->setRange (6., 12) ;
    //xAxis->setRange (40,100) ;
    //yAxis->setRange (0.,1000) ;
    yAxis->rescale() ;
    //rescaleAxes() ;
    this->replot() ;
}

void MyProfilePlot::plotMany (float *x, float *y, int npts, int nplots, int span, float *xrange){

    int i, ip ;
    float maxVal = -1E6 ;


    this->clearGraphs() ;
    this->clearItems() ;

    for (ip=0; ip<nplots; ip++){
        xdata.clear() ;
        ydata.clear () ;

        this->addGraph() ;

        for (i=0; i<npts; i++){
            xdata.append(x[i]) ;
            ydata.append(y[i+ip*span]) ;
            if (y[i+ip*span]>maxVal) maxVal = y[i+ip*span] ;
        }



        graph(ip)->setData(xdata, ydata) ;
        graph(ip)->setPen (QPen(colorPlots[ip])) ;
    }
    xAxis->setRange (xrange[0], xrange[1]) ;
    //xAxis->setRange (40,100) ;
    //yAxis->setRange (0.,1000) ;
    yAxis->rescale() ;
    //rescaleAxes() ;
    this->replot() ;
}

void MyProfilePlot::setOthersXYData (int num, float *x, float *y, int npts){

    int i, inum ;
    xdata.clear() ;
    ydata.clear () ;

    for (inum=0; inum<num; inum++){
    for (i=0; i<npts; i++){
        xdata.append(x[i]) ;
        ydata.append(y[i+npts*i]) ;
    }
    graph(inum+2)->setData(xdata, ydata) ;
    }
    //yAxis->rescale (true) ;
    //escaleAxes() ;
    this->replot() ;




}

void MyProfilePlot::setYData (int graphnum, float *y, int npts){

    int i ;

    xdata.clear() ;
    ydata.clear () ;

    for (i=0; i<npts; i++){
        xdata.append(i) ;
        ydata.append(y[i]) ;
    }
    graph(graphnum)->setData(xdata, ydata) ;

    //yAxis->rescale (true) ;
    rescaleAxes() ;
    this->replot() ;

}

void MyProfilePlot::setYData (int graphnum, QVector<float> vec){

    int i ;
    int npts = vec.count () ;
    xdata.clear() ;
    ydata.clear () ;

    for (i=0; i<npts; i++){
        xdata.append(i) ;
        ydata.append(vec[i]) ;
    }
    graph(graphnum)->setData(xdata, ydata) ;

    //yAxis->rescale (true) ;
    rescaleAxes() ;
    //this->replot() ;

}


void MyProfilePlot::setXYData (int graphnum, QVector<float> xvec, QVector<float>yvec){

    int i ;
    xdata.clear() ;
    ydata.clear() ;
    for (i=0; i<xvec.count(); i++) {
        xdata.append(xvec[i]) ;
        ydata.append(yvec[i]) ;
    }

    graph(graphnum)->setData(xdata, ydata) ;

    //yAxis->rescale (true) ;
    if (rescaleFlag)
        rescaleAxes() ;
    //this->replot() ;

}

void MyProfilePlot::setupPlots (float *data, QList<QString>gname, int npts, int nplots, int ptsToPlot){

    int i ;

    this->clearItems() ;
    this->clearGraphs() ;
    /*
    if (nplots != nprofiles){
        this->clearGraphs() ;
    }
    */
    for (i=0; i<nplots; i++){
        addGraph() ;
        QPen pen (colorPlots[i]) ;
        graph(i)->setPen (pen) ;

        graph(i)->setName (gname[i]) ;
        //graph(i)->rescaleAxes ();
        setYData(i, data+i*npts, ptsToPlot) ;
    }
    QCPItemLine vline (this) ;
    //this->legend->setVisible(true) ;
    rescaleAxes() ;
    //xAxis->setRange (0,);
    //yAxis->rescale() ;
    this->replot() ;
}

/*
void MyProfilePlot::setupPlots (float *data,  int npts, int nplots, int ptsToPlot){

    int i ;

    this->clearItems() ;
    this->clearGraphs() ;

    for (i=0; i<nplots; i++){
        addGraph() ;
        QPen pen (colorPlots[i]) ;
        graph(i)->setPen (pen) ;

        //graph(i)->rescaleAxes ();
        setYData(i, data+i*npts, ptsToPlot) ;
    }
    QCPItemLine vline (this) ;
    //this->legend->setVisible(true) ;
    //rescaleAxes() ;
    this->replot() ;
}
*/

void MyProfilePlot::setupScatterPlot (double *x, double *y, double *coefs, int npts) {
    int i ;
    float  pixval, minx,maxx, maxy ;
    QVector<double> xvals ;
    QVector<double> yvals ;
    QVector<double> xvals2 ;
    QVector<double> yvals2 ;
    this->clearItems() ;

    QCPItemText *eqn_label = new QCPItemText (this) ;

    QString eqn ;


    eqn_label->position->setCoords(12,1200) ;

    eqn.sprintf ("Wavenumber = %5.2f + %5.2f * Bandnumber", coefs[0], coefs[1]) ;
    eqn_label->setText (eqn) ;
    eqn_label->setPen (QPen(Qt::black)) ;
   // addItem (eqn_label) ;
    minx = 1.E9 ;
    maxx = -1.E9 ;
    maxy = -1.E9 ;
    for (i=0; i<npts; i++){
        if (x[i]>maxx) maxx = x[i] ;
        if (x[i]<minx) minx = x[i] ;
        xvals.append(x[i]) ;
        yvals.append(y[i]) ;
    }
    this->clearGraphs() ;
    addGraph() ;
    addGraph() ;
    graph(0)->setScatterStyle (QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue, Qt::white, 5));
    graph(0)->setData (xvals, yvals) ;
    graph(0)->setLineStyle(QCPGraph::lsNone) ;

    for (pixval =minx-2.; pixval<maxx+2.; pixval+=.5){
        xvals2.append(pixval) ;
        yvals2.append(coefs[0]+coefs[1]* pixval) ;


    }
    graph(1)->setData(xvals2,yvals2) ;
    graph(1)->setPen (QPen (Qt::red)) ;
    xAxis->setLabel("Band Number");
    yAxis->setLabel("Wavenumber (cm-1)");
    this->legend->setVisible(false) ;
    this->rescaleAxes () ;
    this->replot() ;
}

void MyProfilePlot::setupScatterPlot (float *x, float *y, double *coefs, int npts) {
    int i ;
    float  pixval, minx,maxx ;
    QVector<double> xvals ;
    QVector<double> yvals ;
    QVector<double> xvals2 ;
    QVector<double> yvals2 ;
    this->clearItems() ;

    QCPItemText *eqn_label = new QCPItemText (this) ;

    QString eqn ;


    eqn_label->position->setCoords(12,1200) ;

    eqn.sprintf ("Wavenumber = %5.2f + %5.2f * Bandnumber", coefs[0], coefs[1]) ;
    eqn_label->setText (eqn) ;
    eqn_label->setPen (QPen(Qt::black)) ;
    //addItem (eqn_label) ;
    minx = 1.E9 ;
    maxx = -1.E9 ;
    for (i=0; i<npts; i++){
        if (x[i]>maxx) maxx = x[i] ;
        if (x[i]<minx) minx = x[i] ;
        xvals.append(x[i]) ;
        yvals.append(y[i]) ;
    }
    this->clearGraphs() ;
    addGraph() ;
    //addGraph() ;
    graph(0)->setScatterStyle (QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue, Qt::white, 5));
    graph(0)->setData (xvals, yvals) ;
    graph(0)->setLineStyle(QCPGraph::lsNone) ;
/*
    for (pixval =minx-2.; pixval<maxx+2.; pixval+=.5){
        xvals2.append(pixval) ;
        yvals2.append(coefs[0]+coefs[1]* pixval) ;


    }
    */
    //graph(1)->setData(xvals2,yvals2) ;
    //graph(1)->setPen (QPen (Qt::red)) ;
    xAxis->setLabel("Band Number");
    yAxis->setLabel("Wavenumber (cm-1)");
    this->legend->setVisible(false) ;
    this->rescaleAxes () ;
    this->replot() ;
}


void MyProfilePlot::mousePressEvent (QMouseEvent *event){
    double x, y ;


    x = xAxis->pixelToCoord(event->x()) ;
    y = yAxis->pixelToCoord(event->y()) ;
    qDebug ("X : %f  Y: %f", x, y) ;
    emit (coordsFound(x, y)) ;
    //setToolTip (QString ("%1, %2").arg(x).arg(y)) ;
    QToolTip::showText (event->globalPos(),
                        QString::number(x)+","+
                        QString::number(y)) ;
}


void MyProfilePlot::setAxesNames (QString xname, QString yname ){
    yAxis->setLabel (yname) ;
    xAxis->setLabel(xname) ;
    this->replot() ;
}



void MyProfilePlot::ShowContextMenu(const QPoint& pos) // this is a slot
{
    // for most widgets
    QPoint globalPos = mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    QAction *openDlg = myMenu.addAction("Adjust Plot Scales");
    connect (openDlg, SIGNAL (triggered()), this, SLOT(startScaleDlg()));

    // ...

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        // something was chosen, do stuff
        int hg = 0 ;


    }
    else
    {
        // nothing was chosen
    }
}


void MyProfilePlot::startScaleDlg() {
    int i, npts = xdata.count() ;

    float xval, yval, xmin=1.E9, xmax=-1E9, ymin=1.E9, ymax=-1E9;

    for (i=0;i<npts; i++){
        xval = xdata.at(i) ;
        yval = ydata.at(i);
        if (xval > xmax) xmax = xval ;
        if (xval < xmin) xmin = xval ;
        if (yval > ymax) ymax = yval ;
        if (yval < ymin) ymin= yval ;
    }

    psd = new PlotScaleDialog (this) ;
    psd->setMinMax (xmin, xmax, ymin, ymax) ;

    connect (psd, SIGNAL (haveValues()), this, SLOT(updateMinMax())) ;
    psd->exec() ;
}


void MyProfilePlot::updateMinMax() {
    float xmin, xmax, ymin, ymax ;
    xmin = psd->xMin ;
    ymin = psd->yMin ;
    xmax = psd->xMax ;
    ymax = psd->yMax ;
    this->xAxis->setRange (xmin, xmax) ;
    this->yAxis->setRange (ymin, ymax) ;
    this->replot() ;

}
