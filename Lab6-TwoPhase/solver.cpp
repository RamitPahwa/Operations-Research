#include <bits/stdc++.h>

#define FOR(i,a,b) for(i=a;i<=b;i++)
#define eps 0.0001

float absolute(float value)
{
    if (value>=0)
        return value;
    else if (value<0)
        return (-value);
}

int main(int argc, char const *argv[])
{
    int n,ni,i,j,k,ge,ee,le,m,chk;
    std::cout << "Enter 1 for maximization, 2 for minimization" << std::endl;
    std::cin >> chk;
    std::cout << "Please enter the number of variables in the equations:" << std::endl;
    std::cin >> ni;
    std::cout << "Please enter the number of >= signs in the constraint equation:" << std::endl;
    std::cin >> ge;
    std::cout << "Please enter the number of = signs in the constraint equation:" << std::endl;
    std::cin >> ee;
    std::cout << "Please enter the number of <= signs in the constraint equation:" << std::endl;
    std::cin >> le;
    m = ge + ee + le;
    std::cout << "Please enter the basic equation to maximize in the form Z=x1+x2+3 ==> 1 1 3" << std::endl;
    float beq[ni + 1];
    FOR(i, 0, ni)
        std::cin >> beq[i];
    float eq[m][ni + 1];
    std::cout << "Please enter the constraint equations with '>=' sign like: x1+x2 >= 20  ==>  1 1 20" << std::endl;
    FOR(i, 0, ge-1)
        FOR(j, 0, ni)
            std::cin >> eq[i][j];
    std::cout << "Please enter the constraint equations with '=' sign like: x1+x2 = 20  ==>  1 1 20" << std::endl;
    FOR(i, ge, ge + ee - 1)
        FOR(j, 0, ni)
            std::cin >> eq[i][j];
    std::cout << "Please enter the constraint equations with '<=' sign like: x1+x2 <= 20  ==>  1 1 20" << std::endl;
    FOR(i, ge + ee, ge + ee + le - 1)
        FOR(j, 0, ni)
            std::cin >> eq[i][j];
    n = ni + ge;
    std::cout << "Initial Constraint Equations" << std::endl;
    FOR(i, 0, m - 1)
    {
        FOR(j, 0, ni)
            std::cout << eq[i][j] << "\t";
        std::cout << std::endl;
    }
    int prow ,pcol;
    double sum = 0.0;
    double temp_sum = 0.0;
    double temp=0.0;
    std::string nbv[2][n];
    double cnbv[n+1];
    double cbv[m];
    std::string bv[2][m];
    std::stringstream num;
    FOR(i, 0, n - 1)
    {
        nbv[0][i] = 'x';
        num << i+1;
        nbv[1][i] = num.str();
        num.str(std::string());
    }
    FOR(i, 0, ni - 1)
        cnbv[i] = beq[i];
    FOR(i, ni, n - 1)
        cnbv[i] = 0;
    cnbv[n] = beq[ni];
    FOR(i, 0, m - 1)
    {
        bv[0][i] = 'z';
        num << i+1;
        bv[1][i] = num.str();
        num.str(std::string());
        cbv[i] = 0;
    }
    float mat[m+1][n+1], mat2[m+1][n+1];
    FOR(i,0,m)
        FOR(j,0,n)
            mat[i][j] = 0;
    float tsum = 0.0;
    FOR(i,0,m-1)
        FOR(j,0,ni-1)
            mat[i][j] = eq[i][j];
    FOR(k,0,ge-1)
        FOR(i,0,ge-1)
            FOR(j,ni+i,ni+i)
                mat[i][j] = -1;
    FOR(i,0,m-1)
        mat[i][n] = eq[i][ni];

    FOR(i,0,n)
    {
        tsum = 0.0;
        FOR(j,0,ge+ee-1)
            tsum = tsum + mat[j][i];
        mat[m][i] = -(tsum);
    }
    std::cout << "Phase 1: Matrix" << std::endl;
    FOR(i,0,m)  //Printing the Matrix after Phase 1 initialization
    {
        if(i == 0)
        {
            std::cout << "V" << "\t";
            FOR(j,0,n-1)
                std::cout << nbv[0][j] << nbv[1][j] << "," << cnbv[j] << "\t";
            std::cout << cnbv[n];
        }
        std::cout << std::endl;
        if(i != m)
            std::cout << bv[0][i] << bv[1][i] << "," << cbv[i] << "\t";
        else
            std::cout << "Z" << "\t";
        FOR(j,0,n)
            std::cout << mat[i][j] << "\t";
    }

    while(1)
    {
        temp = 0; //eps was 0
        FOR(i,0,n-1)
        {
            if(mat[m][i] < temp)
            {
                temp = mat[m][i];
                pcol = i;
            }
        }
        if (temp == 0) //eps was 0
        {
            if(mat[m][n] == 0)
            {
                std::cout << "Proceding to Phase: 2" << std::endl;
                FOR(i,0,n-1)
                {
                    if(nbv[0][i] == "z")
                    {
                        FOR(j,0,m)
                            mat[j][i] = 0;
                    }
                }//made the z columns 0
                FOR(i,0,n-1)
                {
                    temp_sum = 0.0;
                    FOR(j,0,m-1)
                        temp_sum = temp_sum + cbv[j] * mat[j][i];
                    mat[m][i] = temp_sum - cnbv[i];
                }
                temp_sum = 0;
                FOR(j,0,m-1)
                    temp_sum = temp_sum + cbv[j]*mat[j][n];
                mat[m][n] = cnbv[n] + temp_sum;
                FOR(i,0,m)  //Printing the Matrix after iteration
                {
                    if(i == 0)
                    {
                        std::cout << "V" << "\t";
                        FOR(j,0,n-1)
                            std::cout << nbv[0][j] << nbv[1][j] << "," << cnbv[j] << "\t";
                        std::cout << cnbv[n];
                    }
                    std::cout << std::endl;
                    if(i != m)
                        std::cout << bv[0][i] << bv[1][i] << "," << cbv[i] << "\t";
                    else
                        std::cout << "Z" << "\t";
                    FOR(j,0,n)
                        std::cout << mat[i][j] << "\t";
                }

                while(1)
                {
                    temp = 0;
                    FOR(i,0,n-1)
                    {
                        if(mat[m][i] < temp)
                        {
                            temp = mat[m][i];
                            pcol = i;
                        }
                    }
                    if (temp == 0)
                    {
                        std::cout << "\nBasic Feasable Solution: "<< std::endl;
                        if(chk == 2)
                            mat[m][n] = -mat[m][n];
                        std::cout << "The Optimal Value of Z: " << mat[m][n] << std::endl;

                        return 0;
                    }

                    double temp2 = 999999.0;
                    FOR(i,0,m-1)
                    {
                        if(mat[i][pcol] != 0)
                            if((mat[i][n]/mat[i][pcol]) > 0)
                                if((mat[i][n]/mat[i][pcol]) < temp2)
                                {
                                    temp2 = mat[i][n]/mat[i][pcol];
                                    prow = i;
                                }
                    }
                    double pivot = mat[prow][pcol];
                    mat2[prow][pcol] = 1/pivot;
                    FOR(i,0,n)
                        if(i != pcol)
                        {
                            if(absolute(mat[prow][i]/pivot) < eps)
                                mat2[prow][i] = 0;
                            else
                                mat2[prow][i] = mat[prow][i]/pivot;
                        }
                    FOR(i,0,m)
                        if(i != prow)
                        {
                            if(absolute(mat[i][pcol]/pivot) < eps)
                                mat2[i][pcol] = 0;
                            else
                                mat2[i][pcol] = -(mat[i][pcol]/pivot);
                        }
                    FOR(i,0,m)
                        FOR(j,0,n)
                            if(i != prow)
                            {
                                if(j != pcol)
                                {
                                    if(absolute(((pivot*mat[i][j])-(mat[i][pcol]*mat[prow][j]))/pivot) < eps)
                                        mat2[i][j] = 0;
                                    else
                                        mat2[i][j] = ((pivot*mat[i][j])-(mat[i][pcol]*mat[prow][j]))/pivot;
                                }
                            }
                    //Change x to z
                    std::string temp_str[2];
                    temp_str[0] = nbv[0][pcol];
                    temp_str[1] = nbv[1][pcol];
                    nbv[0][pcol] = bv[0][prow];
                    nbv[1][pcol] = bv[1][prow];
                    bv[0][prow] = temp_str[0];
                    bv[1][prow] = temp_str[1];
                    double temp_var = cnbv[pcol];
                    cnbv[pcol] = cbv[prow];
                    cbv[prow] = temp_var;

                    FOR(i,0,m)
                        FOR(j,0,n)
                            mat[i][j] = mat2[i][j];
                    std::cout << "\n\n";
                    std::cout << "Matrix after iteration: " << std::endl;
                    FOR(i,0,m)  //Printing the Matrix after iteration
                    {
                        if(i == 0)
                        {
                            std::cout << "V" << "\t";
                            FOR(j,0,n-1)
                                std::cout << nbv[0][j] << nbv[1][j] << "," << cnbv[j] << "\t";
                            std::cout << cnbv[n];
                        }
                        std::cout << std::endl;
                        if(i != m)
                            std::cout << bv[0][i] << bv[1][i] << "," << cbv[i] << "\t";
                        else
                            std::cout << "Z" << "\t";
                        FOR(j,0,n)
                            std::cout << mat[i][j] << "\t";
                    }
                    std::cout << "\n\n";
                }
            }
            else
            {
                std::cout << "Infeasable Question." << std::endl;
                std::cout << "Value of f = " << mat[m][n] << "\n\n";
                return 0;
            }
        }
        double temp2 = 999999.0;
        FOR(i,0,m-1)
        {
            if(mat[i][pcol] != 0)
                if((mat[i][n]/mat[i][pcol]) > 0)
                    if((mat[i][n]/mat[i][pcol]) < temp2)
                    {
                        temp2 = mat[i][n]/mat[i][pcol];
                        prow = i;
                    }
        }
        double pivot = mat[prow][pcol];
        mat2[prow][pcol] = 1/pivot;
        FOR(i,0,n)
            if(i != pcol)
            {
                if(absolute(mat[prow][i]/pivot) < eps)
                {
                    mat2[prow][i] = 0;
                }
                else
                    mat2[prow][i] = mat[prow][i]/pivot;
            }
        FOR(i,0,m)
            if(i != prow)
            {
                if(absolute(mat[i][pcol]/pivot) < eps)
                    mat2[i][pcol] = 0;
                else
                    mat2[i][pcol] = -(mat[i][pcol]/pivot);
            }
        FOR(i,0,m)
            FOR(j,0,n)
                if(i != prow)
                {
                    if(j != pcol)
                    {
                        if(absolute(((pivot*mat[i][j])-(mat[i][pcol]*mat[prow][j]))/pivot) < eps)
                           mat2[i][j] = 0;
                        else
                            mat2[i][j] = ((pivot*mat[i][j])-(mat[i][pcol]*mat[prow][j]))/pivot;
                    }
                }
        //Change x to z
        std::string temp_str[2];
        temp_str[0] = nbv[0][pcol];
        temp_str[1] = nbv[1][pcol];
        nbv[0][pcol] = bv[0][prow];
        nbv[1][pcol] = bv[1][prow];
        bv[0][prow] = temp_str[0];
        bv[1][prow] = temp_str[1];
        double temp_var = cnbv[pcol];
        cnbv[pcol] = cbv[prow];
        cbv[prow] = temp_var;

        FOR(i,0,m)
            FOR(j,0,n)
                mat[i][j] = mat2[i][j];
        std::cout << "\n\n";
        std::cout << "Matrix after iteration: " << std::endl;
        FOR(i,0,m)  //Printing the Matrix after iteration
        {
            if(i == 0)
            {
                std::cout << "V" << "\t";
                FOR(j,0,n-1)
                    std::cout << nbv[0][j] << nbv[1][j] << "," << cnbv[j] << "\t";
                std::cout << cnbv[n];
            }
            std::cout << std::endl;
            if(i != m)
                std::cout << bv[0][i] << bv[1][i] << "," << cbv[i] << "\t";
            else
                std::cout << "Z" << "\t";
            FOR(j,0,n)
                std::cout << mat[i][j] << "\t";
        }
        std::cout << "\n\n";
    }

    return 0;
}