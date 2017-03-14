#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>


using namespace std;

#define size 15

float mat[size][size],temp[size][size],constant[size],mat_ori[size][size];
int basic[size],non_basic[size];
int slackVar=0,ArtiVar=0,SurpVar=0;
int max_or_min;
int n,m,i,j,k;
bool infinite=false;
bool infeasible=false;
int counter=0;
int tableNo=1;

void makeOriginal()
{
  for(i=0;i<=m;i++)
  {
    for(j=0;j<=n+SurpVar;j++)
    {
      mat[i][j]=mat_ori[i][j];
    }
  }

}

float absolute(float value)
{
  if(value>=0)
    return value;
  else if (value<0)
    return (-value);
}

int findMaxNegativeRow()
{
	int index=-1;
  float minValue=9999999;
  for(i=0;i<m;i++)
  {
    if(mat[i][n+SurpVar]>0)
      continue;
    else if (mat[i][n+SurpVar]==0)
    {
      infinite=true;
      return -1;
    }
    else
    {
      if (mat[i][n+SurpVar]<minValue)
      {
        minValue=mat[i][n+SurpVar];
        index=i;
      }
    }


  }
  return index;

}
int findCol(int pivotRow)
{
  int index=-1;
  float minValue=999999;
  for(i=0;i<n+SurpVar;i++)
  {
    if(mat[pivotRow][i]>=0)
      continue;
    else if(mat[pivotRow][i]<0)
    {
      // printf("%f%f",mat[m][i],mat[pivotRow][i]);
      if(absolute(mat[m][i]/mat[pivotRow][i])<=minValue)
      {
        minValue=absolute(mat[m][i]/mat[pivotRow][i]);
        index=i;
      }
    }

  }

  return index;  

}
void replaceTable()
{
  for(i=0;i<=m;i++)
  {
    for (j=0;j<=n+counter;j++)
    {
      mat[i][j]=temp[i][j];
    }
  }

}
void printTable()
{
  printf("======================================================\n");
  printf("Table %d",tableNo);
  for (i=0;i<=m;i++)
    {
      for(j=0;j<=n+SurpVar;j++)
      {
        printf("%f  ",mat[i][j]);
      }
      printf("\n");
    }
    printf("=====================================================\n");
    tableNo++;


}

void solver(int nindex)
{
  int pivotRow,pivotCol;
  int iter=1;
  makeOriginal();
  while(pivotRow=findMaxNegativeRow()!=-1 && iter!=nindex)
  {
    //printTable();
    if(pivotCol=findCol(pivotRow)==-1)
    {
      infeasible=true;
      return;
    }
    for(i=0;i<m;i++)
    {

      for(j=0;j<n+SurpVar;j++)
      {
        if(i==pivotRow && j==pivotCol)
          temp[i][j]=1.0/mat[i][j];
        else if(i==pivotRow)
          temp[i][j]=mat[i][j]/mat[pivotRow][pivotCol];
        else if (j==pivotCol)
          temp[i][j]=-1*mat[i][j]/mat[pivotRow][pivotCol];
        else 
          temp[i][j]=(mat[pivotRow][pivotCol]*mat[i][j]-mat[pivotRow][j]*mat[i][pivotCol])/mat[pivotRow][pivotCol];
      }

    }
    replaceTable();
    iter++;
  }
  printTable();


}
void solver()
{

  int pivotRow,pivotCol;
  printTable();
  makeOriginal();
  while((pivotRow=findMaxNegativeRow())!=-1)
  {
    
    if((pivotCol=findCol(pivotRow))==-1)
    {
      infeasible=true;
      return;
    }
    for(i=0;i<=m;i++)
    {

      for(j=0;j<=n+SurpVar;j++)
      {
        if(i==pivotRow && j==pivotCol)
          temp[i][j]=1.0/mat[i][j];
        else if(i==pivotRow)
          temp[i][j]=mat[i][j]/mat[pivotRow][pivotCol];
        else if (j==pivotCol)
          temp[i][j]=(-1*mat[i][j])/mat[pivotRow][pivotCol];
        else 
          temp[i][j]=(mat[pivotRow][pivotCol]*mat[i][j]-mat[pivotRow][j]*mat[i][pivotCol])/mat[pivotRow][pivotCol];
      }

    }
    replaceTable();
    printTable();
  }
  


}


int main()
{
	
	printf("Enter the number of Variables:");
	scanf("%d",&n);
	printf("Enter the number of Equations:");
	scanf("%d",&m);
	// calculate();
	printf("Enter 1 for Maximization problem and -1 for for Minimization problem\n");
  	scanf("%d",&max_or_min); 
    int in;
  	for(i=0;i<m;i++)
  	{
  		cout<<"Enter 1.Ax<=b 2.Ax>=b 3.Ax=b"<<endl;
  		cin>>in;
  		if(in==1)
  		{
  			slackVar++;
  			for(j=0;j<n;j++)
  			{
  				scanf("%f",&mat[i][j]);
  			}
  			scanf("%f",&constant[i]);

  		}
  		else if(in==2)
  		{
  			ArtiVar++;
  			SurpVar++;
  			for(j=0;j<n;j++)
  			{  
  				scanf("%f",&mat[i][j]);
  			}
  			for(k=0;k<m;k++)
  			{
  				if(k==i)
  					mat[k][j+counter]=-1;
  				else
  					mat[k][j+counter]=0;
  			}
        for(j=0;j<=n+counter;j++)
        {
          mat[i][j]=-mat[i][j];
        }
        scanf("%f",&constant[i]);
        constant[i]=-constant[i];
        counter++;

  		}
      else if(in==3)
      {
        ArtiVar++;
        SurpVar++;
        for(j=0;j<n;j++)
        {
          scanf("%f",&mat[i][j]);
          // mat[i+1][j]=-mat[i][j];
        }
        i++;
        m++;
        for(j=0;j<n;j++)
          mat[i][j]=-mat[i-1][j];
        for(k=0;k<m;k++)
        {
          if(k==i)
            mat[k][j+counter]=1;
          else
            mat[k][j+counter]=0;
        }
        counter++;
        scanf("%f",&constant[i]);
        constant[i-1]=constant[i];
        constant[i]=-constant[i];
      }
  	}
    for(i=0;i<m;i++)
    {
      mat[i][n+SurpVar]=constant[i];
    }
    printf("Enter the coefficient of objective function followed by constant");
    for(j=0;j<=n;j++)
    {
      scanf("%f",&mat[m][j]);
      mat[m][j]=max_or_min*mat[m][j];

    }
    for(i=0;i<=m;i++)
  {
    for(j=0;j<=n+SurpVar;j++)
    {
      mat_ori[i][j]=mat[i][j];
    }
  }
    //solver();
    //solver(1);
    // solver(2);

    solver();
    



}