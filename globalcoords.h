#ifndef GLOBALCOORDS_H
#define GLOBALCOORDS_H

#include <QObject>

class GlobalCoords
{
public:
    GlobalCoords();
    int starts, startl ;
    float degPerPixel ;
    void xy2latlon (int x, int y, float *lon, float *lat) ;
};

#endif // GLOBALCOORDS_H
