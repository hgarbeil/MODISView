#include "plotscaledialog.h"
#include "ui_plotscaledialog.h"

PlotScaleDialog::PlotScaleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotScaleDialog)
{
    ui->setupUi(this);
    xMin = 0 ;
    xMax = 0 ;
    yMin = 0 ;
    yMax = 0 ;
}

PlotScaleDialog::~PlotScaleDialog()
{
    delete ui;
}


void PlotScaleDialog::setMinMax (float xmin, float xmax, float ymin, float ymax){

    QString str = QString ("%1").arg(xmin) ;
    ui->xminLE->setText (str);
    str = QString ("%1").arg(xmax) ;
    ui->xmaxLE->setText (str);
    str = QString ("%1").arg(ymin) ;
    ui->yminLE->setText (str);
    str = QString ("%1").arg(ymax) ;
    ui->ymaxLE->setText (str);

}

void PlotScaleDialog::on_applyButton_clicked()
{
    xMin = ui->xminLE->text().toFloat() ;
    xMax = ui->xmaxLE->text().toFloat() ;
    yMin = ui->yminLE->text().toFloat() ;
    yMax = ui->ymaxLE->text().toFloat() ;
    emit (haveValues()) ;
}

void PlotScaleDialog::on_closeButton_clicked()
{
    //this->destroy(true);
    PlotScaleDialog::close() ;
}
