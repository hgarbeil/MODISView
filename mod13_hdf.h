#ifndef MOD13_HDF_H
#define MOD13_HDF_H
#include "mfhdf.h"
#include <QFile>
#include <QDebug>
#include <string>
using namespace std;

class MOD13_hdf
{
public:
    MOD13_hdf();
    ~MOD13_hdf() ;
    void openHDF (char *infile);
    int getStack (char *infile) ;
    void getYearMonth(string) ;
    string curfile ;
    uint16 *ndvidata ;
    float *stackf, startlat, startlon, pixspace ;
    int starts, startl, ns, nl ;
    int month, year ;
private :
    int32 sds_id ;
};

#endif // MOD13_HDF_H
