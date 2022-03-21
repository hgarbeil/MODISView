#ifndef IMWIDGET_H
#define IMWIDGET_H
#include <QPainter>
#include <QPoint>
#include <QToolTip>
#include <QWidget>
#include <QMouseEvent>

class Imwidget : public QWidget
{
    Q_OBJECT
public:
    explicit Imwidget(QWidget *parenqqqt = nullptr);
    ~Imwidget() ;
    void paintEvent (QPaintEvent *event) ;
    void mousePressEvent (QMouseEvent *event) ;
    void loadQImage (unsigned short *data, int ns, int nl) ;
    void loadQImage_alt (unsigned short *data, int ns, int nl) ;
    void setNightFlag (bool nflag) ;
    QImage *qim, *qim_0, *qim_1 ;
    bool userFlag, imageLoaded, nightFlag ;

    unsigned short uMax, uMin ;
signals:
    void clickedXY(int *xy);
public slots:
};

#endif // IMWIDGET_H
