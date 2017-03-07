#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iomanip>

using namespace std;

#define M 10000
#define size 15

// Variables involved in the Problem 

float mat[size][size],temp[size][size];
float matconst[size];
float objectiveCoef[size]={0};
int rc[size]={0};            //Right coefficient matrix used to indicate artificial variable 
int slackVar=0,artiVar=0,surpVar=0;
int max_or_min;
int solution_index[size];
bool infinite=false;
bool unbounded=false;
int counter=0;
int n,m,i,j,k;
int table_no=1;

void input()
{

  string inequality;
  
  printf("Enter the number of variables\n");
  scanf("%d",&n);
    
  printf("Enter number of equations\n");
  scanf("%d",&m);
  //needs to be updated 
  for (i=0;i<m;i++)
    {
      solution_index[i]=m+i+1;
    }

  printf("Enter 1 for Maximization problem and -1 for for Minimization problem\n");
  scanf("%d",&max_or_min);  
  for(i=0;i<m;i++)
  { 
    cout<<"Enter Sign of the Equation"<<endl;
    cin>>inequality;
    cout<<"Enter Coefficients"<<endl;
    if(inequality.at(0)=='<')
      { 

        for (j=0;j<n;j++)
        {
          scanf("%f",&mat[i][j]);
        }
        slackVar++;
      }
    else if (inequality.at(0)=='>')
    {
      for (j=0;j<n;j++)
        {
          scanf("%f",&mat[i][j]);
        }
      for (k=0;k<m;k++)
        {
          if(k!=i)
            {
              mat[k][j+counter]=0;
            }
          else
              mat[k][j+counter]=-1;
        }
      rc[i]=-max_or_min*M;  
      counter++;
    }
    else 
    {
      for (j=0;j<n;j++)
          {
            scanf("%f",&mat[i][j]);

          }
          rc[i]=-max_or_min*M;
    }

  }
  cout<<"Enter the Constant term for the equations"<<endl;  
  for(i=0;i<m;i++)
    { 
      scanf("%f",&mat[i][n+counter]);
    }
  cout<<"Enter the Coefficient of the Objective Function"<<endl;
  
  for (i=0;i<n;i++)
  {
    scanf("%f",&objectiveCoef[i]);
  }
  

  for(i=0;i<=n+counter;i++)
    {

      for(j=0;j<m;j++)
      {
        mat[m][i]=mat[m][i]+rc[j]*mat[j][i];
      }
      mat[m][i]=mat[m][i]-objectiveCoef[i];
    }

}

int getMinFromLastRow()
{

  int index=-1;
  float minValue=0;
  for(i=0;i<n+counter;i++)
  {
    if(mat[m][i]>0)
      continue;
    else if(mat[m][i]==0)
      {infinite=true;}
    else if (mat[m][i]<0 )
    {
      if (mat[m][i]<minValue)
      {
        minValue=mat[m][i];
        index=i;
      }

    }
  }
  return index;
}
int getMinRowIndex(int pivotColumn)
{
    int index=-1;
    float minValue=9999999;
    for(i=0;i<m;i++)
    {
      if(mat[i][pivotColumn]<=0)
        continue;
      else if ((mat[i][n+counter]/mat[i][pivotColumn])<minValue)
        { 
          minValue=mat[i][n+counter]/mat[i][pivotColumn];
          index=i;
          }
    }
    return index;
}
void makeNewTableau(){

  cout << "======================================================" <<endl;
  cout << "\t\t Table " <<::table_no++ << endl << endl;
  for(int i = 0 ; i <=m ; i++){
    for(int j = 0 ; j <= n+counter; j++){
        mat[i][j] = temp[i][j];
        cout << setw(10)<<mat[i][j] << "\t";
    }     
    cout << endl;
  }
  cout << "======================================================" <<endl;   
}

void solver()
{ 

  cout << "======================================================" <<endl;
  cout << " \t  Initial Simplex Table " << endl << endl;
     for(int i = 0 ; i <= m ; i++){
          for(int j = 0 ; j <= n+counter ; j++){
               cout << setw(10)<< mat[i][j] << "\t";
           }
           cout << endl; 
     }          
  cout << "======================================================" <<endl;

  int pivotCol,pivotRow;
  while((pivotCol=getMinFromLastRow())!=-1)
  {
    if((pivotRow=getMinRowIndex(pivotCol))==-1)
    {
      unbounded=true;
      return;
    }
    // replaceSolution(pivotalColumn,pivotalRow);
    for(int i = 0 ; i <= m ; i++){
               for(int j = 0 ; j <= n+counter; j++){
                    if(i == pivotRow && j == pivotCol)
                         temp[i][j] = 1/mat[i][j];
                    else if(i == pivotRow)     
                         temp[i][j] = (mat[i][j])/mat[pivotRow][pivotCol];          
                    else if(j == pivotCol)
                         temp[i][j] = ((-1)*mat[i][j])/mat[pivotRow][pivotCol];
                    else{
                        temp[i][j] = ((mat[pivotRow][pivotCol]*mat[i][j]) - (mat[pivotRow][j]*mat[i][pivotCol]))/mat[pivotRow][pivotCol]; 
                    }
               }
          }
          makeNewTableau();

  }

}

int main()
{

  input();
  solver();
  for(i=0;i<=m;i++)
  {
    for(j=0;j<=n+counter;j++)
    {
      cout<<"   "<<mat[i][j];
    }
    cout<<endl;
  }
  




}