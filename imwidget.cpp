#include "imwidget.h"

Imwidget::Imwidget(QWidget *parent) : QWidget(parent)
{
    qim = 0L ;
    qim_0 = 0l;
    qim_1 = 0l ;
    userFlag = false ;
    uMax = 32768 ; ;
    uMin = 0 ;
    imageLoaded = false ;
    nightFlag = true ;
}


Imwidget::~Imwidget(){
    if (qim_0)
        delete qim_0 ;
    if (qim_1)
        delete qim_1 ;
}


void Imwidget::loadQImage (unsigned short *dat, int ns, int nl) {
    int   i, npix ;
    float fval, scale, off ;
    float min, max, mnmx[2] ;
    QRgb *line ;
    if (qim_0) delete qim_0 ;
    qim_0 = new QImage (ns, nl, QImage::Format_ARGB32) ;

    unsigned char cbyte ;
    min=1.E9 ;
    max=-1.E9 ;
    npix = nl * ns ;


    if (userFlag) {
        max = uMax ;
        min = uMin ;
    } else {
        for (i=0; i<npix; i++){
            fval = *(dat+i) ;
            if (fval <=0) continue ;
            if (fval > max) max = fval ;
            if (fval< min) min = fval ;
        }
        mnmx[0] = min ;
        mnmx[1] = max ;
        uMax = max ;
        uMin = min ;
        //emit (setMnMx ((float*)&mnmx[0])) ;

    }
    //max = 10000 ;
    //min = 0 ;
    qDebug () << "Min max is : "<< min << "   " << max ;
    scale = 255. / (max - min) ;
    for (i=0; i<nl; i++){
        line = (QRgb *) qim_0->scanLine(i) ;
        for (int j=0; j<ns; j++){
            fval = *(dat+i*ns+j) ;
            fval = ((fval - min) * scale) ;
            if (fval < 0.) fval = 0. ;
            if (fval >255.) fval = 255. ;
            cbyte = (unsigned char)fval ;
            *(line+j) = qRgb ( cbyte, cbyte, cbyte) ;
        }
    }
    imageLoaded = true ;
    qim = qim_0 ;
}

void Imwidget::loadQImage_alt (unsigned short *dat, int ns, int nl) {
    int   i, npix ;
    float fval, scale, off ;
    float min, max, mnmx[2] ;
    QRgb *line ;
    if (qim_1) delete qim_1 ;
    qim_1 = new QImage (ns, nl, QImage::Format_ARGB32) ;

    unsigned char cbyte ;
    min=1.E9 ;
    max=-1.E9 ;
    npix = nl * ns ;

    if (userFlag) {
        max = uMax ;
        min = uMin ;
    } else {
        for (i=0; i<npix; i++){
            fval = *(dat+i) ;
            if (fval <=0) continue ;
            if (fval > max) max = fval ;
            if (fval< min) min = fval ;
        }
        mnmx[0] = min ;
        mnmx[1] = max ;
        uMax = max ;
        uMin = min ;
        //emit (setMnMx ((float*)&mnmx[0])) ;

    }
    scale = 255. / (max - min) ;
    for (i=0; i<nl; i++){
        line = (QRgb *) qim_1->scanLine(i) ;
        for (int j=0; j<ns; j++){
            fval = *(dat+i*ns+j) ;
            fval = ((fval - min) * scale) ;
            if (fval < 0.) fval = 0. ;
            if (fval >255.) fval = 255. ;
            cbyte = (unsigned char)fval ;
            *(line+j) = qRgb ( cbyte, cbyte, cbyte) ;
        }
    }

}

void Imwidget::setNightFlag (bool nflag){
    nightFlag = nflag ;
    update() ;
}


void Imwidget::paintEvent(QPaintEvent *event) {
    int w, h ;

    if (nightFlag){
        qim = qim_0 ;
    } else
        qim = qim_1 ;

    w = this->width() ;
    h = this->height() ;
    if (!imageLoaded)
        return ;
    QPainter p (this) ;
    p.drawImage (QRect(0,0,1320,700), *qim) ;


}

void Imwidget::mousePressEvent (QMouseEvent *ev){

    int xy[2];
    QToolTip::showText (ev->globalPos(),
    QString::number(ev->pos().x())+","+QString::number(ev->pos().y())) ;
    xy[0] = ev->pos().x() ;
    xy[1] = ev->pos().y() ;
    this->clickedXY(xy);
    //repaint() ;
}
