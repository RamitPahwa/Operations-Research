#include <stdio.h>
#include <math.h>


/*
	Input various values
*/
void Entry()
{

	int i,j,k;
	int n,m;
	printf("Enter the Number of Variable visible: \n");
	scanf("%d",&n);
	double *objectiveFunction;
	objectiveFunction=(double *)malloc(n*sizeof(double));
	//Entry for Objective Function
	printf("Enter the Coefficient of objective function [Variable values will be positive always]\n");
	for (i=0;i<n;i++)
		{
			printf("Coefficient of x%d :- ",i+1);
			scanf("%lf",&objectiveFunction[i]);
		}
	//Entry for Conditions
	printf("Enter the Number of equations:");
	scanf("%d",&m);
	double **condCoef;
	condCoef=(double **)malloc(m*sizeof(double *));
	printf("Enter Value of Condition Coefficient:\n");
	for (i=0;i<m;i++)
		{
			condCoef[i]=(double *)malloc(n*sizeof(double));
		}	
		for (i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{	
				printf("Enter coefficient of variable x%d in equation %d :",j+1,i+1);
				scanf("%lf",&condCoef[i][j]);
			}	
		}	
	double *condb;
	condb=(double *)malloc(m*sizeof(double));
	printf("Enter Value of condition b values:\n");
	for (i=0;i<m;i++)
		{
			printf("Enter the value b %d :",i+1);
			scanf("%lf",&condb[i]);

		}


}

/*
	Driver for the program
*/
void main()
{

	Entry();

}