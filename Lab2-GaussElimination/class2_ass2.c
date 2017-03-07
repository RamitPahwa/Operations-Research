#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count=0;
void swap(float **a,int row1,int row2,int n)
{

	int i;
	float temp;
	for(i=0;i<n;i++)
	{
		temp=a[row1][i];
		a[row1][i]=a[row2][i];
		a[row2][i]=temp;
	}
}

void printMatrix(float **a,int n)
{
		int i,j;
	for(i=0;i<n;i++){

			for(j=0;j<=n;j++){

				printf("%0.4lf  ",a[i][j]);

			}
			printf("\n");
		}
}
void check(float **a,int n,int i,int j)
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
int fact(int no){
	if(no==0)
		return 1;
	if (no==1)
		return 1;

	else 
	{
		return (no*fact(no-1));
	}


}
void solveGaussElimination(float **a,int n,float *b,float *solution)
{	

	int i,j,k;
	float sum=0.0;
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
				float ratio=(a[j][i]/a[i][i]);
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

}
void generateCombination(int data[],float **a,int start,int index,int m,int n,float * b,float **solution_main){

		int i,j=0,k=0;
		
		if (index==m){
			float **a_sub;
			a_sub=(float ** )malloc(m*sizeof(float * ));
			float *solution,*solution_final;
			solution=(float *)malloc(m*sizeof(float));
			solution_final=(float *)malloc(n*sizeof(float));
			for (i=0;i<n;i++)
			{
				solution[i]=0.0;
			}
			for (j=0;j<m;j++)
				{a_sub[j]=(float *)malloc(m*sizeof(float));}
			for (j=0;j<m;j++){
				for (k=0;k<m;k++){

					a_sub[j][k]=a[j][data[k]];
				}
			}

			solveGaussElimination(a_sub,m,b,solution);
			for(j=0;j<n;j++)
			{
				solution_final[j]=0.0;
			}
			for (k=0;k<m;k++)
				{	
					solution_final[data[k]]=solution[k];
				}
			 for (j=0;j<n;j++)
			 {
			 	solution_main[count][j]=solution_final[j];
			 }
			 count++;
			return;

		}

		

		for (i=start; i<=n-1 && n-i >= m-index; i++)
    {
        data[index] = i;
        generateCombination(data,a, i+1, index+1, m,n,b,solution_main);
    }



}
int max(float *extremeValue,int size)
{
	float max=extremeValue[0];
	int max_index=0;
	int i;
	for (i=0;i<size;i++)
	{
		if(extremeValue[i]>=max)
			{
				max=extremeValue[i];
				max_index=i;
			}
	}
	return max_index+1;
	}
void main(){

	int n,m,i,j,k=0;
	float er,sum=0.0;
	float *z;
	printf("\n Enter the number of variables in condition [n] :");
	scanf("%d",&n);
	printf("\n Enter the number of equation in condition [m] :");
	scanf("%d",&m);
	z=(float *)malloc((n+m)*sizeof(float));
	printf("Enter the coefficient of fuction to be optimized\n");
	for(i=0;i<n;i++)
	{
		printf("Value of coefficient of x%d :",i+1);
		scanf("%f",&z[i]);
	}
	
	if (m==0)
	{
		printf("No Solution");
		exit(0);
	}
	float **a;
	
	float *b;
	int data[m];
	
	a=(float ** )malloc(m*sizeof(float * ));
	for (j=0;j<m;j++)
		a[j]=(float *)malloc((n+m+1)*sizeof(float));

	printf("Enter Value of Matrix A:\n");
	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{	
			printf("Enter coefficient of variable x%d in equation %d :",j+1,i+1);
			scanf("%f",&a[i][j]);
		}
	}
	for (i=n;i<(n+m);i++){

		for(j=0;j<m;j++){

			if((i-n)==j)
				a[j][i]=1.0;
			else
				a[j][i]=0.0;

		}

	}
	b=(float *)malloc(m*sizeof(float));
	printf("Enter Value of Matrix b:\n");
	for (i=0;i<m;i++)
	{
		printf("Enter the value b %d :",i+1);
		scanf("%f",&b[i]);

	}
	int total_solution=fact(n+m)/(fact(m)*fact(n));
	//Solution main containing all feasible solution
	float **solution_main;
	solution_main=(float ** )malloc(total_solution*sizeof(float * ));
	for (j=0;j<total_solution;j++)
		solution_main[j]=(float *)malloc((n+m)*sizeof(float));
	//extreme points are basic feasible solution
	float **extremepoints;
	extremepoints=(float ** )malloc(total_solution*sizeof(float * ));
	for (j=0;j<total_solution;j++)
		extremepoints[j]=(float *)malloc((n+m)*sizeof(float));
	//extremeValue will contain values at extreme points
	float *extremeValue;
	extremeValue=(float *)malloc(total_solution*sizeof(float));

	generateCombination(data,a,0,0,m,n+m,b,solution_main);
	printf("Feasible Solution Are as Follows:\n");
	for (i=0;i<total_solution;i++)
		{	printf("%d. ",i+1);
			for(j=0;j<n+m;j++)
			{

				printf("x%d= %0.3lf     ",j+1,solution_main[i][j]);
			}
			printf("\n");
		}
		int flag;
	for(i=0;i<total_solution;i++)
		{
			for(j=0;j<n+m;j++)
			{
				if(solution_main[i][j]<0.0)
					{
						flag=0;
						break;
					}
				else 
					flag=1;
			}

			if(flag!=0)
			{	
			 				for (j=0;j<n+m;j++)
							{
								extremepoints[k][j]=solution_main[i][j];
			 				}
			 				k++;
			}
			
		}
						printf("Extreme Point is :\n");
						for(i=0;i<k;i++){
							for (j=0;j<n+m;j++)
							{
								printf("Value of x %d is : %f\n",j+1,extremepoints[i][j]);
			 				}
			 				printf("---------------------------\n");
							}
						for(i=0;i<k;i++){
							for (j=0;j<n+m;j++)
							{	
								sum=sum+z[j]*extremepoints[i][j];
								
			 				}
			 				extremeValue[i]=sum;
			 				sum=0.0;
							}

			int maxindex=max(extremeValue,k);
			printf("Maximum value of Objective Function is is %f",extremeValue[maxindex]);
			printf("\n\n Solution is obtained at :\n");
			for (j=0;j<n+m;j++)
							{
								printf("\nValue of x %d is : %f",j+1,extremepoints[maxindex][j]);
			 				}
			printf("\n");
}