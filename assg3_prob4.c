#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>
#include <math.h>

double f(double x) 
{return exp(-x*x);}
float g(float x)
{ return exp(-x*x/4.0)/sqrt(2.0);}

int main()
{ 
	int i,n=1024;
	double f_x[n],k[n],w[n],x_min=-90.0,x_max=90.0,dx=(x_max-x_min)/(n-1);
	fftw_complex f_k[n];
	fftw_plan p;
	printf("%f",dx);

	for (i=0;i<n;i++)
	{ 
		f_x[i]=f(x_min+i*dx);
	}

	p = fftw_plan_dft_r2c_1d(n,f_x,f_k, FFTW_ESTIMATE);
	fftw_execute(p);

	for (i=0;i<n/2;i++)
	{ k[i]=2.0*M_PI*i/n/dx;
	w[i]=dx/sqrt(2.0*M_PI)*(cos(k[i]*x_min)*f_k[i][0]+sin(k[i]*x_min)*f_k[i][1]);}
	for (i=n/2;i<n;i++)
	{
		k[i]=(i-n)*2.0*M_PI/n/dx;
		w[i]=dx/sqrt(2.0*M_PI)*(cos(k[i]*x_min)*f_k[n-i][0]-sin(k[i]*x_min)*f_k[n-i][1]);
	}

FILE*fptr;
	fptr=fopen("assg3_prob4.csv","w");
		for (i=n/2;i<n;i++)
		{
		fprintf(fptr,"%f, %f, %f\n", k[i],w[i],g(k[i]));}
		for (i=0;i<n/2;i++)
		{
		fprintf(fptr,"%f, %f, %f\n", k[i],w[i],g(k[i]));}
		fclose(fptr);
fftw_destroy_plan(p);

return 0;
}
