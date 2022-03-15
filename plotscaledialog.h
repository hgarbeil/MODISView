#ifndef PLOTSCALEDIALOG_H
#define PLOTSCALEDIALOG_H

#include <QDialog>

namespace Ui {
class PlotScaleDialog;
}

class PlotScaleDialog : public QDialog
{
    Q_OBJECT



public:
    explicit PlotScaleDialog(QWidget *parent = 0);
    void setMinMax (float xmin, float xmax, float ymin, float ymax);
    ~PlotScaleDialog();
    float xMin, xMax, yMin, yMax ;

private slots:
    void on_applyButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::PlotScaleDialog *ui;

signals :
    void haveValues() ;
};

#endif // PLOTSCALEDIALOG_H
