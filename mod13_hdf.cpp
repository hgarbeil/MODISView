#include "mod13_hdf.h"
#include <string>

using namespace std;

MOD13_hdf::MOD13_hdf()
{

    // dataset 4 is nighttime LST
    // dataset 0 is daytime LST
    startl = 700 ;
    starts = 1080 ;
    pixspace = 180. / 3600. ;
    startlat = 90.f - (startl * pixspace) ;
    startlon = starts * pixspace ;
    ns = 1320 ;
    nl = 700 ;
    ndvidata = new uint16 [ns * nl];
    stackf = 0L ;
    //stack = 0L ;

}


MOD13_hdf::~MOD13_hdf (){
    if (ndvidata)
        delete [] ndvidata ;

    if (stackf)
        delete [] stackf ;

}

void MOD13_hdf::openHDF (char *infile){

    // for monthly LST MOD13 Product
    // datasets
    // 0 - LST_Day_CMG
    // 5 - LST_Night_CMG


    char name[240], attrb_name[240] ;
    int32 n_datasets, n_fileattrs, sds_id, rank, dim_sizes[3],num_type, attributes,count ;
    int32 start[2], stride[2], edge[2] ;
    double scaleval;
    start[0] = startl ;
    start[1] = starts ;
    edge[0] = nl ;
    edge[1] = ns ;
    stride[0] = 1 ;
    stride[1] = 1 ;

    QFile *qf = new QFile (infile) ;
    if (!qf->exists()){
        qDebug() << ("Uhoh") ;
    }
    int32 sd_id = SDstart (infile, DFACC_RDONLY) ;
    if (sd_id<=0) {
        qDebug()<< "Uhoh again";
    }
    SDfileinfo(sd_id, &n_datasets, &n_fileattrs);
    qDebug () <<"datasets "<< n_datasets<< "   file attrs "<< n_fileattrs ;
    for (int i=0; i<n_datasets; i++){
        sds_id = SDselect(sd_id, i);

        SDgetinfo (sds_id, name, &rank, dim_sizes, &num_type, &attributes ) ;
        qDebug() <<i << "  " << name ;
        if (i==0){
            qDebug ()<<"Number of attributes : " << attributes ;

            int attnum = SDfindattr (sds_id, "scale_factor") ;
            SDreadattr (sds_id, attnum, &scaleval);

            qDebug()<< dim_sizes[0] << " " << dim_sizes[1] << " " << rank ;
            SDreaddata(sds_id, start, stride, edge, ndvidata) ;
        }



        for (int j=0; j<attributes; j++){
            SDattrinfo (sds_id, j, name, &num_type, &count) ;
            //qDebug () << j << "  " << name<< "  " << count ;

        }
    }

    qDebug() << "ndvi val is " << ndvidata [(nl/2)*ns+(ns/2)] ;

    SDend (sd_id) ;
}


int MOD13_hdf::getStack (char *infile) {
    // The stack file is our flat file containing a band for each of the 20+ years, stacked as unsigned short arrays ns * nl * nyears
    // No scaling was applied therefore to get degrees K needs to be multiplied by .02
    uint16 *stack ;
    long nbytes ;
    int nyears ;

    // this is the scaled LST data, clean out
    if (stackf) {
        delete [] stackf ;
    }

    string directory, stackfile;

    string filename (infile) ;
    const size_t last_slash_idx = filename.rfind('/');
    if (std::string::npos != last_slash_idx)
    {
        directory = filename.substr(0, last_slash_idx);
    }
    qDebug () <<"Filename directory is "<< directory.c_str() ;
    stackfile = directory + string("/outarr_day") ;
    QFile qf (stackfile.c_str()) ;
    qf.open (QIODevice::ReadOnly) ;
    nbytes = qf.size() ;
    // allocate memory for the stack
    stack = new uint16 [nbytes/2] ;
    stackf = new float [nbytes/2] ;
    nyears = int(nbytes / (ns * nl * 2)) ;
    qDebug () << "number of years "<< nyears ;
    qf.read ((char *)stack, nbytes) ;
    qf.close() ;
    for (long i=0; i<nbytes/2; i++){
        stackf[i] = stack[i] / 10000. ;
    }



    qDebug() << "this year is " << stackf[long(ns * nl * 20)+350 * ns + 660] ;
    delete [] stack ;
    return (nyears) ;
}
