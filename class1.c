#include <stdio.h>
#include <math.h>

void main()
{

	int n,i,j;
	double er,sum;
	printf("\n Enter the size of the matrix [n] :");
	scanf("%d",&n);
	printf("\n Enter the stopping criteria :");
	scanf("%lf",&er);
	double a[n][n];
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{	
			printf("Enter value i= %d j=%d :",i,j);
			scanf("%lf",&a[i][j]);
		}
	}
	double b[n];
	for (i=0;i<n;i++)
	{
		printf("Enter the value b %d :",i);
		scanf("%lf",&b[i]);
	}
	double x0[n],x[n];
	for (i=0;i<n;i++)
	{
		x0[i]=0;
		x[i]=0;
	}
	int key =0 ;
	do{
	for (i=0 ;i<n;i++)
	{
		sum=b[i];
		
		for (j=0;j<n;j++)
		{
			if (j!=i)
			{
				sum=sum-a[i][j]*x0[j];	
			}
		}
		x[i]=sum/a[i][i];
		if(abs((x[i]-x0[i])/x[i])>er)
		{
			printf("iteration %d : ",i+1);			
			key=1;
			x0[i]=x[i];
		}	

	}
	}while(key==0);
	for (i=0;i<n;i++)
	{
		printf("Value of x %d is : %lf",i+1,x[i]);
	}
	
	
}
