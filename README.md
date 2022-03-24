# QHdfView 

MODIS MOD11 and MOD13 Global MODIS Monthly Global Analysis Software

## Description

This program will allow a user to read in a MOD11 land surface temperature hdf global monthly file or a MOD13 NDVI hdf global monthly file. The program has been set to extract a region of interest of the continental United States.

## Requirements

### Source Code and Build
This is a source code only repository. To properly use this program for a specific platform (MacOS, Windows or Linux) a Qt Programming environment and HDF 4 development libraries are required. Additional add-ons such as QtCustomPlot have been added to the repository. This software has been developed on a Macbook Pro running El Capitan. Qt and HDF versions installed on this machine are the following.

  * Qt 5.11.3 clang 64 bit
    * Note that much newer versions of Qt exist but because of my hardware and os requirements, Qt 5.11 is the latest functional version in my environment.
    * https://www.qt.io/ 
  * HDF 4.2.15
    * https://support.hdfgroup.org/release4/obtain.html
    
 
### Data
The program is designed to read in global NDVI (MOD13 and MOD11) datasets. These files are available via the NASA data portals for MODIS land data products. In addition to the MOD11 and / or MOD13 files that the user would like to analyze, the program uses cube files which consist of the MOD11 night and day LST data for continental USA and MOD13 NDVI data for the same area with each band or slice of the cube being a year starting at 2001 and ending in 2021. These file cubes were constructed from the 2001 - 2021 MOD11 and MOD13 global files.  
