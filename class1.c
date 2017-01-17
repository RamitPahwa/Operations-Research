#include <stdio.h>
#include <math.h>
#include <stdlib.h>
float positive(float check){

	if (check>0.0)
		return check;
	else 
		return (-check);
}



void main()
{

	int n,i,j;
	float er,sum;
	printf("\n Enter the size of the matrix [n] :");
	scanf("%d",&n);
	printf("\n Enter the stopping criteria :");
	scanf("%f",&er);
	float a[n][n];
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{	
			printf("Enter value i= %d j=%d :",i,j);
			scanf("%f",&a[i][j]);
		}
	}
	float b[n];
	for (i=0;i<n;i++)
	{
		printf("Enter the value b %d :",i);
		scanf("%f",&b[i]);
	}
	float x0[n],x[n];
	for (i=0;i<n;i++)
	{
		x0[i]=0;
		x[i]=0;
	}
	int key =1 ;
	while(key==1)
	{
	for (i=0 ;i<n;i++)
	{
		sum=b[i];
		
		for (j=0;j<n;j++)
		{
			if (j!=i)
			{
				sum=sum-a[i][j]*x0[j];
				printf("%lf",sum);	
			}
		}
		x[i]=sum/a[i][i];
		printf("x=%lf \n",x[i]);
		printf("check=%lf \n",(x[i]-x0[i])/x[i]);
		float check=(x[i]-x0[i])/x[i];
		
		if(positive(check)>er)
		{
			// printf("iteration %d :\n ",i+1);
			// for (i=0;i<n;i++)
			// {
			// 	printf("Value of x %d is : %lf",i+1,x[i]);
			// 	}
			printf("here inside if");			
			key=1;
			x0[i]=x[i];
		}	
		else 
		{
			key=0;
		}
		printf("key =%d\n",key);
		getchar();

	}
	}
	for (i=0;i<n;i++)
	{
		printf("Value of x %d is : %lf",i+1,x[i]);
	}
	
	
	
	
}
