#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>

double f(double x) 
{ 
	if (x==0.0)
	{return 1.0;}
	else
	{return sin(x)/x;}
}

float g(float x) 
{ if (fabs(x)<=1.0)
	{return sqrt(M_PI/2.0);}
	else
	{return 0.0;}}


int main (void)
{
int i,n;
double f_x[2*n],f_k[2*n], k[n],dx,x_min,x_max;
x_min=-30.0*M_PI;
x_max=30.0*M_PI; 
dx=(x_max-x_min)/(n-1);
n=1024;

for (i=0;i<n;i++)
{
	REAL(f_x,i) = REAL(f_k,i)=f(x_min+dx*i); 
	 IMAG(f_x,i)=IMAG(f_k,i) = 0.0;
	}

	gsl_fft_complex_radix2_forward (f_k, 1, n); 

for (i=0;i<n/2;i++)
{   k[i]=2.0*M_PI*i/n/dx;
	REAL(f_k,i)=dx/sqrt(2.0*M_PI)*(cos(k[i]*x_min)*REAL(f_k,i)+sin(k[i]*x_min)*IMAG(f_k,i));}
for (i=n/2;i<n;i++)
{    k[i]=2.0*M_PI*(i-n)/n/dx;
	REAL(f_k,i)=dx/sqrt(2.0*M_PI)*(cos(k[i]*x_min)*REAL(f_k,i)+sin(k[i]*x_min)*IMAG(f_k,i));}


FILE*fptr;
	fptr=fopen("assg3_prob3.csv","w");
     printf("%f %f",k[n/2],k[n-1]);
		for (i=n/2;i<n;i++)
		{
		fprintf(fptr,"%f, %f, %f\n", k[i],REAL(f_k,i),g(k[i]));}
		for (i=0;i<n/2;i++)
		{
		fprintf(fptr,"%f, %f, %f\n", k[i],REAL(f_k,i),g(k[i]));}
		fclose(fptr);

return 0;
}
