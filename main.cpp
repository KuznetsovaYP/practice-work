#include <math.h>
#include <iostream>
#include <vector>
#include "plant.h"



using namespace std;


void enter( int k, vector<double>&A)
{
    for (int i=0; i<k; i++)
        cin>>A[i];
    return;
}

void t1(int N, int k, vector<double>&a, vector<vector<double>>&X,vector<double>&T, vector<double>&M)
{
    vector<double> s(k);
    s[0]=0;
    for (int i=0; i<k; i++)
    {
        for (int j=0; j<N; j++)
            s[i]=s[i]+X[i][j];
    }
    for(int i=0; i<k; i++)
         {
        for (int j=0; j<N; j++)
        {
            T[i] = a[i]*s[i]/N;
            cout<<"chanel number: "<<M[i]<<" mesurement: "<<X[i][j]<<"  TEP1: "<<T[i]<<endl;
        }
         }
    return;
}

void t2(int N, int k, vector<double>&b, vector<double>&g, vector<vector<double>>&X,vector<double>&T, vector<double>&M)
{
    vector<double> c(k);
    c[0]=0;
    for (int i=0; i<k; i++)
    {
        for (int j=0; j<N; j++)
            c[i]=c[i]+pow((X[i][j]-g[i]),2);
    }
    for(int i=0; i<k; i++)
         {
        for (int j=0; j<N; j++)
    {
        T[i] = b[i]*c[i]/N;
        cout<<"chanel number: "<<M[i]<<" mesurement: "<<X[i][j]<<"  TEP2: "<<T[i]<<endl;
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
    enter(k,M);

    cout<<"Enter constants ai: ";
    enter(k,a);

    cout<<"Enter constants bi: ";
    enter(k,b);

    cout<<"Enter constants gi: ";
    enter(k,g);

    vector<double>TEP1(k);
    vector<double>TEP2(k);

    for(int j=0; j<N; j++)
    {
        for (int i=0; i<k; i++)
            X[i][j]=plant_measure(M[i], plant);
    }

    t1(N,k,a,X,TEP1,M);
    t2(N,k,b,g,X,TEP2,M);


    return 0;
}
