#include <stdio.h>
#include <stdlib.h>

#include "PerlinNoise.h"

//creates a random floating point number between 0 and 1.0 (non-inclusive of 1.0)
#define randf() ((double)rand()/(1.0+(double)RAND_MAX))

//creates a random floating point number between -1 and 1, inclusive of both
#define prandf() (((double)rand()/((double)RAND_MAX/2.0))-1.0)
#define THRESHOLD (0.5f)


#define SIZE (4.0)
#define INTSIZE (20)
#define STEP (SIZE/(double)INTSIZE)
int scaler( int, int, double, double, double);

int main(int argc, char **argv)
{
    int i,j;
    double noise[INTSIZE][INTSIZE];
   
    double min=0.0,max=0.0;

   SetAmplitude(10.0);
   SetFrequency(3.0);
   SetPersistence(0.7);
   SetOctaves(atoi(argv[1]));


    double curx,cury;
    for(i=0; i<INTSIZE; i++)
    {
       curx = (double)i * STEP;
        for(j=0; j<INTSIZE; j++)
        {
            cury = (double)j * STEP;
            noise[i][j]  = noise2d(curx, cury); 
      
            if(noise[i][j] > max)
            {
               max = noise[i][j];
            }
            if(noise[i][j] < min)
            {
               min = noise[i][j];
            }
        
        }
        
    }

    for(i=0;i<INTSIZE;i++){for(j=0;j<INTSIZE;j++){
      int current = scaler(0,65535,min,max,noise[i][j]);
      if(current < 30000)
      {
         printf("  ");
      }
      else if(current < 40000)
      {
         printf(". ");
      }
      else if(current < 50000)
      {
         printf("x ");
      }
      else
      {
         printf("^ ");
      }
    }
    printf("\n");
    }
    return 0;
}

int scaler(int minint, int maxint, double mindub, double maxdub, double prescale)
{
   int intrange = maxint - minint;
   double dubrange = maxdub - mindub;

   prescale -= mindub;

   double perc = prescale/dubrange;

   int output = perc * intrange;

   output+=minint;

   return output;

}
