#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void gauss_elim(int m,float A[][2*m+1]){
	int i,j,k,t;
	float c,sum=0,AA[m+1][2*m+1];
	for (i=1; i<=m; i++) {
        // Search for maximum in this column
        float maxEl = (A[i][i]);
        int maxRow = i;
        for (k=i+1; k<=m; k++) {
            if ((A[k][i]) > maxEl) {
                maxEl = (A[k][i]);
                maxRow = k;
            }
        }
        // Swap maximum row with current row (column by column)
        for (k=i; k<=m;k++) {
            float tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }
        // Make all rows below this one 0 in current column
        for (k=i+1; k<=m; k++) {
            c = -A[k][i]/A[i][i];
            for (j=i; j<=2*m; j++) {
                if (i==j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] += c * A[i][j];
                }
            }
        }
    }

	// for(j=1;j<=m;j++){
	// 	for(i=1;i<=m;i++){
	// 		if(i>j){
	// 			c=A[i][j]/A[j][j];
	// 			for(k=1;k<=2*m;k++){
	// 				A[i][k]-=c*A[j][k];
	// 			}
	// 		}

	// 	}
	// }
	for(i=1;i<=m;i++)
		for(j=1;j<=2*m;j++)
			AA[i][j]=A[i][j];
	
	for(i=1;i<=m;i++){
		for(j=1;j<=2*m;j++){
			if(i!=j) A[i][j]/=A[i][i];
		}
		A[i][i]=1;
	}

	printf("\n");
	for(i=m-1;i>=1;i--){
		for(j=2;j<=2*m;j++){
			t=i+1;
			sum=0;
			for(k=i+1;k<=m;k++){
				sum+=A[k][j]*AA[i][t++];
			}
			A[i][j]-=sum;
		}
	}
}

void compute_Inv(int m,float B[][m+1],float Binv[][m+1]){
	float A[m+1][2*m+1];
	int i,j;
	for(i=1;i<=m;i++){
		for(j=1;j<=m;j++)
			A[i][j]=B[i][j];
		for(j=m+1;j<=2*m;j++)
			A[i][j]=j-m==i?1:0;
	}
	gauss_elim(m,A);
	for(i=1;i<=m;i++)
		for(j=1;j<=m;j++)
			Binv[i][j]=	A[i][j+m];
}

void compute_Y(int m,float cB[],float Binv[][m+1],float Y[]){
	int i,j;
	float sum;
	for(i=1;i<=m;i++){
		sum=0;
		for(j=1;j<=m;j++)
			sum+=cB[j]*Binv[j][i];
		Y[i]=sum;
	}
}

void compute_cB(int m,float z[],int basis[],float cB[]){
	int i;
	for(i=1;i<=m;i++)
		cB[i]=z[basis[i]];
}

void compute_xB(int m,float Binv[][m+1],float b[],float xB[m+1]){
	int i,j;
	float sum=0;
	for(i=1;i<=m;i++){
		sum=0;
		for(j=1;j<=m;j++)
			sum+=Binv[i][j]*b[j];
		xB[i]=sum;
	}
}

bool x_not_In(int m,int x,int basis[]){
	int i;
	for(i=1;i<=m;i++)
		if(x==basis[i]) return false;
	return true;
}

void RevisedSimplex(int n,int m,float a[][n+1],float b[],float z[],float B[][m+1],int basis[]){
	printf("Entered\n");
	int i,j,k,min_index,min_index2;
	for(i=1;i<=m;i++){
		for(j=1;j<=m;j++)
			printf("%0.4f ",B[i][j]);
		printf("\n");
	}
	printf("Basis ");
	for(i=1;i<=m;i++)
		printf("%d ",basis[i]);
	printf("\n");
	float xB[m+1],cB[m+1],Binv[m+1][m+1],Y[m+1],sum,min=0;
	compute_Inv(m,B,Binv);
	printf("Binv\n");
	for(i=1;i<=m;i++){
		for(j=1;j<=m;j++)
			printf("%0.4f ",Binv[i][j]);
		printf("\n");
	}
	compute_cB(m,z,basis,cB);
	compute_xB(m,Binv,b,xB);
	//step 1
	compute_Y(m,cB,Binv,Y);
	printf("\n");
	for(i=1;i<=m;i++)
		printf("%0.4f ",cB[i]);
	printf("\n");
	for(i=1;i<=m;i++)
		printf("%0.4f ",xB[i]);
	printf("\n");
	for(i=1;i<=n;i++){
		if(x_not_In(m,i,basis)){
			sum=0;
			for(j=1;j<=m;j++){
				sum+=Y[j]*a[j][i];
			}
			sum-=z[i];
			if(min>sum){
				min=sum;
				min_index=i;// computing entering variable
			}
		}
	}
	if(min==0){
		sum=0;
		for(i=1;i<=m;i++){
			printf("X[%d] = %f\n",basis[i],xB[i]);
			sum+=cB[i]*xB[i];
		}
		printf("Z = %f\n", sum);
		return;
	}
	//step 2
	else{
		printf("Entered step 2\n");
		float alpha[m+1];
		for(i=1;i<=m;i++){
			sum=0;
			for(j=1;j<=m;j++){
				sum+=Binv[i][j]*a[j][min_index];
			}
			alpha[i]=sum;
		}
		for(i=1;i<=m;i++)
			printf("%0.4f ", alpha[i]);
		printf("\n");
		min=10000000;
		printf("Theta ");
		for(i=1;i<=m;i++){
			if(alpha[i]!=0){
				if(min>xB[i]/alpha[i] && xB[i]/alpha[i]>0){
					printf("%0.4f ",xB[i]/alpha[i]);
					min=xB[i]/alpha[i];
					min_index2=basis[i];// computing leaving variable
				}
			}
		}
	//step 3
		printf("\nEntered step 3\n");
		for(i=1;i<=m;i++){
			if(basis[i]==min_index2){
				basis[i]=min_index;
				for(j=1;j<=m;j++)
					B[j][i]=a[j][min_index];
				break;
			}
		}
		RevisedSimplex(n,m,a,b,z,B,basis);
	}
}



int main(){
	int n,m,i,j;
	printf("Enter n and m\n");
	scanf("%d%d",&n,&m);
	printf("Enter the coefficient matrix\n");
	float a[m+1][n+1],b[m+1],z[n+1],B[m+1][m+1];
	int basis[m+1];
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
			scanf("%f",&a[i][j]);
	printf("Enter the constant matrix\n");
	for(i=1;i<=m;i++)
		scanf("%f",&b[i]);
	printf("Enter the objective function\n");
	for(i=1;i<=n;i++)
		scanf("%f",&z[i]);
	for(i=1;i<=m;i++)
		basis[i]=n-m+i;
	for(i=1;i<=m;i++)
		for(j=1;j<=m;j++)
			B[i][j]=i==j?1:0;
	RevisedSimplex(n,m,a,b,z,B,basis);
	// RevisedSimplex(n,m,a,b,z,B,basis);
	// RevisedSimplex(n,m,a,b,z,B,basis);
	// RevisedSimplex(n,m,a,b,z,B,basis);
}