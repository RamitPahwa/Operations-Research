#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iomanip>
#include <stdlib.h>

using namespace std;

#define M 1000000
#define size 15

// Variables involved in the Problem 

float mat[size][size],temp[size][size],BFS[2*size][2*size];
float mat_ori[size][size],temp_ori[size][size];
float b_global[size];
float objectiveCoef[size]={0};
int rc[size]={0};            //Right coefficient matrix used to indicate artificial variable 
int slackVar=0,artiVar=0,surpVar=0;
int max_or_min;
int solution_index[size];
int non_basic[size];
bool infinite=false;
bool unbounded=false;
int counter=0,Bcounter=0;
int n,m,i,j,k;
int table_no=1;
int Bcount=0;



void input()
{

  string inequality;
  
  printf("Enter the number of variables\n");
  scanf("%d",&n);
    
  printf("Enter number of equations\n");
  scanf("%d",&m);

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
          BFS[i][j]=mat[i][j];
          mat_ori[i][j]=mat[i][j];
        }
        for (k=0;k<m;k++)
        {
          if(k!=i)
            {
              BFS[k][j+Bcounter]=0;
            }
          else
              BFS[k][j+Bcounter]=1;
        }
        Bcounter++;
        slackVar++;
      }
    else if (inequality.at(0)=='>')
    {
      artiVar++;
      surpVar++;
      for (j=0;j<n;j++)
        {
          scanf("%f",&mat[i][j]);
          BFS[i][j]=mat[i][j];
          mat_ori[i][j]=mat[i][j];
        }
      for (k=0;k<m;k++)
        {
          if(k!=i)
            {
              mat[k][j+counter]=0;
              mat_ori[k][j+counter]=0;
              BFS[k][j+Bcounter]=0;
              BFS[k][j+Bcounter+1]=0;
            }
          else
              {
                mat[k][j+counter]=-1;
                mat_ori[k][j+counter]=-1;
                BFS[k][j+Bcounter]=1;
                BFS[k][j+Bcounter+1]=-1;
              }

        }
        Bcounter=Bcounter+2;
      rc[i]=-max_or_min*M;  
      counter++;
    }
    else 
    {
      artiVar++;
      for (j=0;j<n;j++)
          {
            scanf("%f",&mat[i][j]);
            BFS[i][j]=mat[i][j];
            mat_ori[i][j]=mat[i][j];

          }
            for (k=0;k<m;k++)
             {
                if(k!=i)
                {
                  BFS[k][j+Bcounter]=0;
                }
                else
                  BFS[k][j+Bcounter]=1;
              }
            Bcounter++;
          rc[i]=-max_or_min*M;
    }

  }
  for (i=0;i<m;i++)
    {
      solution_index[i]=m+i+1+surpVar;
    }
  for(i=0;i<n+counter;i++)
  {
    non_basic[i]=i+1;
  }
  cout<<"Enter the Constant term for the equations"<<endl;  
  for(i=0;i<m;i++)
    { 
      scanf("%f",&mat[i][n+counter]);
      b_global[i]=mat[i][n+counter];
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
void replaceSolution(int pivotCol,int pivotRow)
{
  int temp;
  temp=non_basic[pivotCol];
  non_basic[pivotCol]=solution_index[pivotRow];
  solution_index[pivotRow]=temp;

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
    replaceSolution(pivotCol,pivotRow);
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
        solution_main[Bcount][j]=solution_final[j];
       }
       Bcount++;
      return;

    }

    

    for (i=start; i<=n-1 && n-i >= m-index; i++)
    {
        data[index] = i;
        generateCombination(data,a, i+1, index+1, m,n,b,solution_main);
    }

}
int max(float *extremeValue,int Msize)
{
  float max=extremeValue[0];
  int max_index=0;
  int i;
  for (i=0;i<Msize;i++)
  {
    if(extremeValue[i]>=max)
      {
        max=extremeValue[i];
        max_index=i;
      }
  }
  return max_index+1;
}
void solver(int niter)
{

  int pivotCol,pivotRow;
  int tNO=1;
  for(i=0;i<=m;i++)
  {
    for(j=0;j<=n+counter;j++)
    {
      printf("%f ",mat_ori[i][j]);
    }
  }
  while((pivotCol=getMinFromLastRow())!=-1 && tNO<=niter)
  {
    if((pivotRow=getMinRowIndex(pivotCol))==-1)
    {
      unbounded=true;
      return;
    }
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
          tNO++;
  }
  replaceSolution(pivotCol,pivotRow);

}


int main()
{

  input();
  //solver();
  float **a;
  float *b;
  int data[m];
  
  a=(float ** )malloc(m*sizeof(float * ));
  for (j=0;j<m;j++)
    a[j]=(float *)malloc((n+m+surpVar)*sizeof(float));
  for (i=0;i<m;i++)
  {
    for(j=0;j<n+m+surpVar;j++)
    { 
      a[i][j]=BFS[i][j];
    }
  }
  b=(float *)malloc(m*sizeof(float));
  for (i=0;i<m;i++)
  { 
    b[i]=b_global[i];
  }
  int total_solution=fact(n+m+surpVar)/(fact(m)*fact(n+surpVar));
  float **solution_main;
  solution_main=(float ** )malloc(total_solution*sizeof(float * ));
  for (j=0;j<total_solution;j++)
    solution_main[j]=(float *)malloc((n+m+surpVar)*sizeof(float));                                                                                                
  generateCombination(data,a,0,0,m,n+m+surpVar,b,solution_main);
  int ans=1;
  int choice;
  int flag;
  int endflag=0;
  int mainCounter=0;
  int niter;
  while(ans==1)
  {   
    printf("\n\n                                Menu          \n\n");
    printf("===============================================================================\n");
    printf("1.Basic Feasible  Solution\n");
    printf("2.Number of Iteration to solve the Problem (considering intial as 0)\n");
    printf("3.Non Basic variables\n");
    printf("4.Basic Variables \n");
    printf("5.ith Simplex Table\n");
    printf("6.Optimal solution\n");
    printf("7.Exit\n");
    printf("Enter your choice:");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1: 
          for(i=0;i<total_solution;i++)
          {
            for(j=0;j<n;j++)
            {
              if(solution_main[i][j]<0.0 && solution_main[i][j]>M)
              {
                flag=0;
                break;
              }
              else 
                flag=1;
            }

            if(flag!=0)
            { endflag=1;
              printf("Basic Feasible Solution is :\n");
              for (j=0;j<n;j++)
              {
                printf("Value of x %d is : %lf\n",j+1,solution_main[i][j]);
              }
              printf("---------------------------\n");
            }
            else if(endflag==0 && i==total_solution-1)
              printf("\n\n ANS: No Basic feasible  Solution\n\n");

          }
          break;
          case 2: solver();
                  printf("Number of Iteration:%d\n",table_no);
                  break;
          case 3: 
                  printf("Enter the iteration\n");
                  scanf("%d",&niter);
                  solver(niter);
                  for(i=0;i<n+counter;i++)
                  {

                    printf("Value of Non-Basic x%d\n",non_basic[i]);
                  }
                break;
          case 5:exit(0);break;
        }
   }



 return 0;

}
