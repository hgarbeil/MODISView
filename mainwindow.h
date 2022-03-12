#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include "mfhdf.h"
#include "mod11_hdf.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    MOD11_hdf *mhdf ;
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_nightButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QString infile="" ;
};

#endif // MAINWINDOW_H
