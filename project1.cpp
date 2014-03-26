// reading a text file

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;

float ** matr_Med()
{
  float ** med=new float *[4];
  for(int i=0;i<4;i++)
    med[i]=new float[2];  
  
  med[0][0]=1;
  med[0][1]=1;
  med[1][0]=2;
  med[1][1]=1;
  med[2][0]=4;
  med[2][1]=3;
  med[3][0]=5;
  med[3][1]=4;
  return med;
}

float dist_eucl( float *a, float *b)
{
  float dist = (float)sqrt(pow((a[0]-b[0]),2)+pow((a[1]-b[1]),2));
  return dist;
}

float ** matr_D(float ** med, float * c1, float * c2)
{
 float ** matr_D = new float * [2];
 matr_D[0]=new float [4];
 matr_D[1]=new float [4];
 for (int i=0;i<4;i++)
  {
    matr_D[0][i]=dist_eucl(c1,med[i]);
    matr_D[1][i]=dist_eucl(c2,med[i]);
  }
 return matr_D; 
}

float ** matr_G(float ** m)
{
 float ** matr_G = new float * [2];
 matr_G[0]=new float [4];
 matr_G[1]=new float [4];
 for (int i=0;i<4;i++)
  {
    if(m[0][i]>m[1][i])
     {
      matr_G[0][i]=0;
      matr_G[1][i]=1;
     } 
    else
     {
       matr_G[0][i]=1;
       matr_G[1][i]=0;
     }
  }
 return matr_G; 
}

float * centroid(float ** start, float * G_sub)
{
 float * centroid=new float[2];
 centroid[0]=0;centroid[1]=0;
 int c=0;
 for (int i=0;i<4;i++)
  {
    if(G_sub[i]==1)
     { 
      centroid[0]+=start[i][0];
      centroid[1]+=start[i][1];
      c++;
     }
  }
 centroid[0]/=c;
 centroid[1]/=c;
 return centroid;  
}

int D_diff(float ** A, float ** B)
{
  for(int i=0;i<2;i++)
    for (int h=0;h<4;h++)
    {
      if(A[i][h]!=B[i][h]) return 0;
    }
  return 1;
}

int main () {
	float ** med=matr_Med();
  float * c1=new float[2], * c2=new float[2];
  c1[0]=1;c1[1]=1;
  c2[0]=2;c2[1]=1;
  float ** D=matr_D(med,c1,c2);
  float ** G=matr_G(D);
  cout << "Matrix D" << '\n';
  for(int i=0;i<2;i++)
    {
     for(int h=0;h<4;h++)
      cout << D[i][h] << " " ; 
     cout << '\n';
    }
  cout << "---------------------" << '\n';
  cout << "Matrix G" << '\n';
  for(int i=0;i<2;i++)
    {
     for(int h=0;h<4;h++)
      cout << G[i][h] << " " ; 
     cout << '\n';
    }
  cout << "---------------------" << '\n';
  c1=centroid(med,G[0]);
  c2=centroid(med,G[1]);
  cout << "c1 =" << c1[0]<<"-"<<c1[1] << '\n';
  cout << "c2 =" << c2[0]<<"-"<<c2[1] << '\n';
  /*----------------AGAIN----------------*/
  
  if(D_diff(D,matr_D(med,c1,c2))==1) cout << "STOP" ;
  else 
  {
    D=matr_D(med,c1,c2);
    G=matr_G(D);
    cout << "Matrix D" << '\n';
  for(int i=0;i<2;i++)
    {
     for(int h=0;h<4;h++)
      cout << D[i][h] << " " ; 
     cout << '\n';
    }
  cout << "---------------------" << '\n';
  cout << "Matrix G" << '\n';
  for(int i=0;i<2;i++)
    {
     for(int h=0;h<4;h++)
      cout << G[i][h] << " " ; 
     cout << '\n';
    }
  cout << "---------------------" << '\n';
  c1=centroid(med,G[0]);
  c2=centroid(med,G[1]);
  cout << "c1 =" << c1[0]<<"-"<<c1[1] << '\n';
  cout << "c2 =" << c2[0]<<"-"<<c2[1] << '\n';
  }
  return 0;

}

/*
Medicine A 1 1
Medicine B 2 1
Medicine C 4 3
Medicine D 5 4
sqrt((1-4)^2+(1-3)^2)=

*/