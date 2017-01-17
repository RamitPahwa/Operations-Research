#include <stdio.h>
#include <math.h>
#include <stdlib.h>
float positive(float check){

	if (check>0.0)
		return check;
	else 
		return (-check);
}

int isDiagonallyDominant(double **a_sub,int n)
{
	int i,j;
	int flag=1;
	double sum=0;
		for (i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{	

				if(j!=i){
				
					sum=sum+positive(a_sub[i][j]);
				}
			}
			if(positive(a_sub[i][i])<sum)
			{	
				flag=0;
				return flag;
			}

		}
	return flag;	
}

void main()
{

	int n,i,j;
	float er,sum;
	printf("\n Enter the size of the matrix [n] :");
	scanf("%d",&n);
	printf("\n Enter the stopping criteria :");
	scanf("%f",&er);
	double **a;
	a=(double ** )malloc(n*sizeof(double * ));
	for (j=0;j<n;j++)
		a[j]=(double *)malloc(n*sizeof(double));
	printf("Enter Value of Matrix A:\n");
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{	
			printf("Enter coeficient of variable x%d in equation %d :",j+1,i+1);
			scanf("%lf",&a[i][j]);
		}
	}
	float b[n];
	printf("Enter Value of Matrix b:\n");
	for (i=0;i<n;i++)
	{
		printf("Enter the value b %d :",i+1);
		scanf("%f",&b[i]);
	}
	float x0[n],x[n];
	for (i=0;i<n;i++)
	{
		x0[i]=0;
		x[i]=0;
	}
	int key =1 ;
	if (!isDiagonallyDominant(a,n)){

		printf("not Diagionally Dominant(printing original guess)\n");
		key=0;

	}
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
			}
		}
		x[i]=sum/a[i][i];
		float check=(x[i]-x0[i])/x[i];
		
		if(positive(check)>er)
		{			
			key=1;
			x0[i]=x[i];
		}	
		else 
		{
			key=0;
		}

	}
	}
	printf("Solutions:\n");
	printf("---------------------------------------------------------------\n");
	for (i=0;i<n;i++)
	{
		printf("Value of x %d is : %lf \n",i+1,x[i]);
	}
	printf("---------------------------------------------------------------\n");

}
