#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>

float f(float x) 
{ 
	if (x==0.0)
	{return 1.0;}
	else
	{return sin(x)/x;}
}

float g(float x) 
{ 
	if (fabs(x)<=1.0)
	{return sqrt(M_PI/2.0);}
	else
	{return 0.0;}
}

int main()
{ 
	int n,i;
	float x_min,x_max,dx,w[n],k[n],an[n];
	fftw_complex y_x[n],y_k[n];
	fftw_plan p;
	p=fftw_plan_dft_1d(n,y_x,y_k,FFTW_FORWARD,FFTW_ESTIMATE);
	
	n=1024;
	x_min=-30.0*M_PI;
	x_max=30.0*M_PI;
	dx=(x_max-x_min)/(float)(n-1);

	for (i=0;i<n;i++)
	{if(i<n/2)
		{k[i]=M_PI*2.0*(float)i/(float)n/dx ;}
		else
		{k[i]=M_PI*2.0*(float)(i-n)/(float)(n)/dx;}
	y_x[i][0]=f(x_min+dx*(float)i);
       	y_x[i][1]=0.0; 
	}

	FILE*fptr;
	fptr=fopen("assg3_prob2.csv","w");
	fftw_execute(p); 

	for(i=0;i<n;i++) 
	{ w[i]=dx*sqrt(1.0/2.0/M_PI)*(cos(-x_min*k[i])*y_k[i][0]-sin(-x_min*k[i])*y_k[i][1]);
		an[i]=g(k[i]);}
		for (i=n/2;i<n;i++)
		{
		fprintf(fptr,"%f, %f, %f\n", k[i],w[i],an[i]);}
		for (i=0;i<n/2;i++)
		{
		fprintf(fptr,"%f, %f, %f\n", k[i],w[i],an[i]);}
		fclose(fptr);
	fftw_destroy_plan(p);
	return 0;
}

	
