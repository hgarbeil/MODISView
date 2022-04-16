#ifndef MOD11_HDF_H
#define MOD11_HDF_H
#include "mfhdf.h"
#include <QFile>
#include <QDebug>
#include <string>
using namespace std ;

class MOD11_hdf
{
public:
    MOD11_hdf();
    ~MOD11_hdf() ;
    void openHDF (char *infile);
    void getYearMonth (string fname) ;
    int getStack (char *infile) ;
    uint16 *nightdata, *daydata ;
    float *stackf, *daystackf, startlat, startlon, pixspace ;
    int starts, startl, ns, nl, year, month ;
private :
    int32 sds_id ;
};

#endif // MOD11_HDF_H
