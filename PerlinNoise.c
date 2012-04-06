#include "PerlinNoise.h"

//default parameters to 0 -- these should be set via
//the setter functions

static double  persistence =  0.0;
static double  amplitude   =  0.0;
static double  frequency   =  0.0;
static int     octaves     =  0;
static int     random_seed =  0;

static double total(double x, double y);
static double getvalue(double x, double y);
static double interpolate(double x, double y, double a);
static double noise(int x, int y);

void SetPersistence(double np)
{
   persistence = np;
}

void SetAmplitude(double na)
{
   amplitude = na;
}

void SetFrequency(double nf)
{
   frequency = nf;
}

void SetOctaves(int no)
{
   octaves = no;
}

void SetSeed(int ns)
{
   random_seed = 2 + ns*ns;
}

double noise2d(double x, double y)
{
   return amplitude * total(x,y);
}

static double total(double x, double y)
{
   double t = 0.0;
   double amp = 1.0;
   double freq = frequency;
   int i = 0;

   for(i=0;i < octaves; i++)
   {
      t+=getvalue(y*freq+random_seed, x*freq+random_seed) * amp;
      amp *= persistence;
      freq *= 2;
   }
   return t;
}

// 2d example... this should be good
//
//   1     2     3     4
//
//
//   5     6     7     8
//             *
//
//   9     a     b     c                    
//
//
//   d     e     f     g
//   we need noise values cetered around 6, 7, a & b


static double getvalue(double x, double y)
{
   //don't fuck up the zero case.
   int Xint = (x>0)?(int)x:(int)x-1;
   int Yint = (y>0)?(int)y:(int)y-1;

   double Xfrac = x - Xint;
   double Yfrac = y - Yint;

   double n01 = noise(Xint-1, Yint-1);
   double n02 = noise(Xint+1, Yint-1);
   double n03 = noise(Xint-1, Yint+1);
   double n04 = noise(Xint+1, Yint+1);
   double n05 = noise(Xint-1, Yint);
   double n06 = noise(Xint+1, Yint);
   double n07 = noise(Xint, Yint-1);
   double n08 = noise(Xint, Yint+1);
   double n09 = noise(Xint, Yint);

   double n12 = noise(Xint+2, Yint-1);
   double n14 = noise(Xint+2, Yint+1);
   double n16 = noise(Xint+2, Yint);

   double n23 = noise(Xint-1, Yint+2);
   double n24 = noise(Xint+1, Yint+2);
   double n28 = noise(Xint, Yint+2);

   double n34 = noise(Xint+2, Yint+2);

   double x0y0 = 0.0625*(n01+n02+n03+n04) + 0.125*(n05+n06+n07+n08) + 0.25*(n09);
   double x1y0 = 0.0625*(n07+n12+n08+n14) + 0.125*(n09+n16+n02+n04) + 0.25*(n06);
   double x0y1 = 0.0625*(n05+n06+n23+n24) + 0.125*(n03+n04+n09+n28) + 0.25*(n08);
   double x1y1 = 0.0625*(n09+n16+n28+n34) + 0.125*(n08+n14+n06+n24) + 0.25*(n04);

   double v1 = interpolate(x0y0, x1y0, Xfrac);
   double v2 = interpolate(x0y1, x1y1, Xfrac);
   double fin = interpolate(v1, v2, Yfrac);

   return fin;
}

static double interpolate(double x, double y, double a)
{
   double nega = 1.0 - a;
   double negasq = nega * nega;
   double fac1 = 3.0 * (negasq) - 2.0 * (negasq * nega);
   double asq = a * a;
   double fac2 = 3.0 * asq - 2.0 * (asq * a);

   return x * fac1 + y * fac2;
}

static double noise(int x, int y)
{
   int n = x + y * 57;
   n = (n<<13)^n;
   int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
   return 1.0 - (double)(t) * 0.931322574615478515625e-9;
}






