#include <math.h>
#include <iostream>
#include <vector>
#include "plant.h"



using namespace std;


void enter(int n, int k, vector<double>&A)
{
    for (int i=n; i<=k; i++)
        cin>>A[i];
    return;
}

void t1(int N, int k, vector<double>&a, vector<vector<double>>&X,vector<double>&T, vector<double>&M)
{
    vector<double> s(k);
    s[1]=0;
    for (int i=1; i<=k; i++)
    {
        for (int j=1; j<=N; j++)
            s[i]=s[i]+X[i][j];
    }
    for(int i=1; i<=k; i++)
         {
        for (int j=1; j<=N; j++)
        {
            T[i] = a[i]*s[i]/N;
            cout<<M[i]<<' '<<X[i][j]<<' '<<T[i]<<'\t';
        }
         }
    return;
}

void t2(int k, int N, vector<double>&b, vector<double>&g, vector<vector<double>>&X,vector<double>&T, vector<double>&M)
{
    vector<double> c(k);
    c[1]=0;
    for (int i=1; i<=k; i++)
    {
        for (int j=1; j<=N; j++)
            c[i]=c[i]+pow((X[i][j]-g[i]),2);
    }
    for(int i=1; i<=k; i++)
         {
        for (int j=1; j<=N; j++)
    {
        T[i] = b[i]*c[i]/N;
        cout<<M[i]<<' '<<X[i][j]<<' '<<T[i]<<'\t';
    }
         }
    return;
}

int main()
{
    int k, N;

    Plant plant;
    plant_init(plant);

    cout<<"Enter the number of polling channels: ";
    cin>>k;
    cout<<"Enter the number of polls for each channel: ";
    cin>>N;
    vector<double>M(k);
    vector<double>a(k);
    vector<double>b(k);
    vector<double>g(k);
    vector<vector<double>>X(k,vector<double>(N));

    cout<<"Enter the survey channel numbers: ";
    enter(1,k,M);

    cout<<"Enter constants ai: ";
    enter(1,k,a);

    cout<<"Enter constants bi: ";
    enter(1,k,b);

    cout<<"Enter constants gi: ";
    enter(1,k,g);

    vector<double>TEP1(k);
    vector<double>TEP2(k);

    for(int j=1; j<=N; j++)
    {
        for (int i=1; i<=k; i++)
            X[i][j]=plant_measure(M[i], plant);
    }

    t1(N,k,a,X,TEP1,M);
    t2(N,k,b,g,X,TEP2,M);

    //таблица

    return 0;
}
