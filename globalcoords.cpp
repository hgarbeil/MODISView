#include "globalcoords.h"

GlobalCoords::GlobalCoords()
{

        startl = 700 ;
        starts = 1080 ;
        degPerPixel = 0.05 ;


}


void GlobalCoords::xy2latlon(int xloc, int yloc, float *lon, float *lat) {

    *lat = 90.f - (yloc + startl) * degPerPixel ;
    *lon = -180.f + (xloc + starts) * degPerPixel ;
    return ;


}
