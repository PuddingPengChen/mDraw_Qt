#ifndef SVG2GCODE_H
#define SVG2GCODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#ifdef _MSC_VER
#include "XGetopt.h"
#else
#include <unistd.h>
#endif
#include <string.h>
#include <float.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
//#define TESTRNG // remove if on linux or osx
//#define DO_HPGL //remove comment if you want to get a HPGL-code

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"
#define GHEADER "G21\nG90\nG92\nM4  P0\n\n" //add here your specific G-codes
//separated with newline \n

#define CUTTERON "M4  P90\n" //I chose this, change to yours or add comment
// or add newline "\n" if not needed
#define CUTTEROFF "M4  P0\n" // same for this

#define GFOOTER "G0 X0 Y0\nM4 P0\n" //end G-code here
#define GMODE "M4\n"
//#define DO_HPGL //uncomment to get hpgl-file named test.hpgl on current folder




typedef struct {
    float x;
    float y;
} SVGPoint;

typedef struct {
    float points[8];
    int city;
    char closed;
} ToolPath;

static SVGPoint bezPoints[64];
static SVGPoint first,last;
static int bezCount = 0;

#ifdef _WIN32
int32_t rand31();
void seedrand(float);
double drand31();
#endif


float distPtSeg(float,float,float,float,float,float);
void cubicBez(float,float,float,float,float,float,float,float,float,int);
int pcomp(const void* a, const void* b);
void calcPaths(SVGPoint* points, ToolPath* paths,int *cities, int *npaths);
void calcBounds(struct NSVGimage* image);
void reorder(SVGPoint* pts, int* cities, int ncity);
void setPrintLaster( char*pon);
void setPrintHead(char *phead);
void setPrintEnd(char *pend);
int svgToGcode(char* p,int);
#ifdef __cplusplus
}
#endif

#endif // SVG2GCODE_H
