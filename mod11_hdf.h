#ifndef MOD11_HDF_H
#define MOD11_HDF_H
#include "mfhdf.h"
#include <QFile>
#include <QDebug>

class MOD11_hdf
{
public:
    MOD11_hdf();
    ~MOD11_hdf() ;
    void openHDF (char *infile);
    void getStack (char *infile) ;
    uint16 *nightdata, *daydata ;
    float *stackf ;
    int starts, startl, ns, nl ;
private :
    int32 sds_id ;
};

#endif // MOD11_HDF_H
