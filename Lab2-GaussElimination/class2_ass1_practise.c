#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(double **a,int row1,int row2,int n)
{

	int i;
	double temp;
	for(i=0;i<n;i++)
	{
		temp=a[row1][i];
		a[row1][i]=a[row2][i];
		a[row2][i]=temp;
	}
}

void printMatrix(double **a,int n)
{
		int i,j;
	for(i=0;i<n;i++){

			for(j=0;j<=n;j++){

				printf("%0.4lf  ",a[i][j]);

			}
			printf("\n");
		}
}
void check(double **a,int n,int i,int j)
{

	int k;
	if(a[i][j]==0.0)
	{
		for(k=0;k<n;k++)
		{
			if(a[k][0]!=0.0)
			{
				swap(a,i,k,n);
				break;
			}
		}
	}

}
void main(){

	int n,m,i,j,k;
	double er,sum=0.0;
	printf("\n Enter the number of variables [n] :");
	scanf("%d",&n);
	if (n==0)
	{
		printf("No Solution");
		exit(0);
	}
	// printf("\n Enter the stopping criteria :");
	// scanf("%lf",&er);
	double **a;
	double *solution;
	double *b;
	solution=(double *)malloc(n*sizeof(double));
	for (i=0;i<n;i++)
	{
		solution[i]=0.0;
	}
	a=(double ** )malloc(n*sizeof(double * ));
	for (j=0;j<n;j++)
		a[j]=(double *)malloc((n+1)*sizeof(double));

	printf("Enter Value of Matrix A:\n");
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{	
			printf("Enter coeficient of variable x%d in equation %d :",j+1,i+1);
			scanf("%lf",&a[i][j]);
		}
	}
	b=(double *)malloc(n*sizeof(double));
	printf("Enter Value of Matrix b:\n");
	for (i=0;i<n;i++)
	{
		printf("Enter the value b %d :",i+1);
		scanf("%lf",&b[i]);

	}
	for(i=0;i<n;i++)
	{
		a[i][n]=b[i];

	}	
	if(a[0][0]==0.0)
	{
		for(k=0;k<n;k++)
		{
			if(a[k][0]!=0.0)
			{
				swap(a,0,k,n);
				break;
			}
		}
	}
	//check still to be applied for eac diagonal element
	for(i=0;i<n;i++)
	{

			for(j=i+1;j<n;j++)
			{
				double ratio=(a[j][i]/a[i][i]);
				for (k=0;k<(n+1);k++)
				{
				
				a[j][k]=a[j][k]-ratio*a[i][k];
				
				}

			}
			

	}
	//printMatrix(a,n);
	for(i=n-1;i>=0;i--)
	{	
		sum=a[i][n];
		for (j=0;j<n;j++)

			{	
				if(i!=j)
				{
					sum=sum-solution[j]*a[i][j];
				}
			}
			solution[i]=sum/a[i][i];

	}	
	for(i=0;i<n;i++)
		printf("%0.2lf",solution[i]);	

}