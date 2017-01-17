#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double positive(double check){

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

double *solveGaussSiedal(int n,double *b,double **a,double er){
	
	int i,j;
	double sum=0;
	double *x;
	double *x0;
	int iteration=0;
	x=(double *)malloc(n*sizeof(double));
	x0=(double *)malloc(n*sizeof(double));
	for (i=0;i<n;i++)
	{

		x0[i]=0;
		x[i]=0;
	}

	int key =1 ;
	if (!isDiagonallyDominant(a,n)){

		printf("not Diagionally Dominant(printing intial guess)\n");
		key=0;

	}
	while(key==1)
	{iteration++;
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
		double check=(x[i]-x0[i])/x[i];
		
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
	return x ;

}

int fact(int no){

	if (no==1)
		{return 1;}

	else 
	{
		return (no*fact(no-1));
	}


}

void generateCombination(int arr[],int data[],double **a,int start,int end ,int index,int m,int n,double * b,double er){

		int j=0,k=0;
		
		double *x,*solution_final;
		x=(double *)malloc(m*sizeof(double));
		solution_final=(double *)malloc(n*sizeof(double));

		if (index==m){
			double **a_sub;
			a_sub=(double ** )malloc(m*sizeof(double * ));
			for (j=0;j<m;j++)
				{a_sub[j]=(double *)malloc(m*sizeof(double));}
			for (j=0;j<m;j++){
				for (k=0;k<m;k++){

					a_sub[j][k]=a[j][data[k]];
				}
			}

			x=solveGaussSiedal(m,b,a_sub,er);
			for(j=0;j<n;j++)
			{
				solution_final[j]=0.0;
			}
			for (k=0;k<m;k++)
				{	
					solution_final[data[k]]=x[k];
				}
				for (j=0;j<n;j++)
				{
				printf("Value of x %d is : %lf\n",j+1,solution_final[j]);
			 	}
			 printf("---------------------------\n");
			return;

		}

		

		for (int i=start; i<=end && end-i+1 >= m-index; i++)
    {
        data[index] = arr[i];
        generateCombination(arr, data,a, i+1, end, index+1, m,n,b,er);
    }



}

void main(){

	int n,m,i,j;
	double er,sum;
	printf("\n Enter the number of variables [n] :");
	scanf("%d",&n);
	printf("\n Enter the number of equation [m] :");
	scanf("%d",&m);
	printf("\n Enter the stopping criteria :");
	scanf("%lf",&er);
	double **a;
	a=(double ** )malloc(m*sizeof(double * ));
	for (j=0;j<m;j++)
		a[j]=(double *)malloc(n*sizeof(double));
	int x= fact(n)/(fact(n)*fact(n-m));
	int arr[n], data[m],dataf[x];
	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{	
			printf("Enter value i= %d j=%d :",i,j);
			scanf("%lf",&a[i][j]);
		}
	}
	double *b;
	b=(double *)malloc(m*sizeof(double));
	for (i=0;i<m;i++)
	{
		printf("Enter the value b %d :",i);
		scanf("%lf",&b[i]);
	}
	for (i=0;i<n;i++)
	{
		arr[i]=i;
	}
	generateCombination(arr,data,a,0,n-1,0,m,n,b,er);
	
}