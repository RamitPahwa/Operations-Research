#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double positive(double check){

	if (check>0.0)
		return check;
	else 
		return (-check);
}

double * solveGaussSiedal(int n,double b[],double *a,double er){
	
	int i,j;
	double sum=0;
	double x[n];
	double x0[n];
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
		double check=(x[i]-x0[i])/x[i];
		
		if(positive(check)>er)
		{
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

	return x;

}

int fact(int no){

	if (no==1)
		{return 1;}

	else 
	{
		return (no*fact(no-1));
	}


}

void generateCombination(int arr[],int data[],double *dataf,int start,int end ,int index,int m){

		int j=0,k=0;
		double a_sub[m][m];
		if (index==m){


			return;

		}

		for (int i=start; i<=end && end-i+1 >= m-index; i++)
    {
        data[index] = arr[i];
        generateCombination(arr, data,dataf, i+1, end, index+1, m);
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
	double a[n][n];
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
	double b[n];
	for (i=0;i<n;i++)
	{
		printf("Enter the value b %d :",i);
		scanf("%lf",&b[i]);
	}
	for (i=0;i<n;i++)
	{
		arr[i]=i;
	}
	generateCombination(arr,data,(double *) a,0,n-1,0,m);
	







}