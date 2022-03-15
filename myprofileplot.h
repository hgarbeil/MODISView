#ifndef MYPROFILEPLOT_H
#define MYPROFILEPLOT_H

#include <qcustomplot.h>
#include <QList>
#include "plotscaledialog.h"

class MyProfilePlot : public QCustomPlot
{
    Q_OBJECT
public:
    bool rescaleFlag ;
    int nprofiles, nptsProfile, nPlots ;
    explicit MyProfilePlot(QWidget *parent = 0);
    ~MyProfilePlot() ;
    void displayLegend(bool) ;
    void setXYData (float *, float *, int) ;
    void setXYData2 (float *, float *, int) ;
    void setXYData (int gnum, float *, float *, int) ;
    void setYData (int gnum, float *, int) ;
    void setYData (int gnum, QVector<float>) ;
    void setXYData (int graphnum, QVector<float> xvec, QVector<float>yvec) ;
    void setOthersXYData (int, float*, float*, int) ;
    void setupPlots (float *profiles, QList<QString>gname, int nptsProfile, int nprofiles, int ptsToPlot) ;
    void setupPlots (float *x, float *profiles, int nptsProfile, int nprofiles, int ptsToPlot) ;
    void setupScatterPlot (double *x, double *y, double *coefs, int npts) ;
    void setupScatterPlot (float *x, float *y, double *coefs, int npts) ;
    void setAxesNames (QString xname, QString yname) ;
    void plotMany (float *x, float *y, int npts, int nplots, int span) ;
    void plotMany (float *x, float *y, int npts, int nplots, int span, float *xrange) ;

    void setNumberOfPlots (int) ;

    QColor *colorPlots ;
    QVector<double>xdata;
    QVector<double>ydata ;
    QCPItemLine *vline ;

    PlotScaleDialog *psd ;
protected :
    void mousePressEvent(QMouseEvent *event);
signals:
    void coordsFound (double, double) ;
    
public slots:
    void ShowContextMenu(const QPoint& pos) ;
    void startScaleDlg() ;
    void updateMinMax() ;
    
};

#endif // MYPROFILEPLOT_H
