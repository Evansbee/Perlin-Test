#ifndef __ea_perlin_noise_h__
#define __ea_perlin_noise_h__

void SetPersistence(double);
void SetAmplitude(double);
void SetFrequency(double);
void SetOctaves(int);
void SetSeed(int);

double noise2d(double, double);

double p_noise2d(double, double);
double p_noise3d(double, double, double);
double p_noise4d(double, double, double, double);

double s_noise2d(double, double);
double s_noise3d(double, double, double);
double s_noise4d(double, double, double, double);

#endif
