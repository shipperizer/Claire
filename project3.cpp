// reading a text file

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;
const int CLUSTER_MAX_SIZE=200;

float ** matrixGen(char * filename, int &rows)
{
  cout << "Be sure that the file has no more than 5000 rows" << '\n'; 
  string line;
  string splitter="";
  rows=0;
  float ** matrix=new float *[5000];
  ifstream myfile (filename);

  if (myfile.is_open())

  {
    int i=0,h=0,j=0;
    float * tmp=new float[2];
    while ( getline (myfile,line) && j<5000 )
    { 
      i=0;h=0;
      while(i<line.length() && h<3)
      {
        splitter="";
        while(line[i] == char(32) && i<line.length()) i++;
        while(line[i] != char(32) && i<line.length() ) 
          {
           if(h>0) splitter+=line[i];
           i++;
          }
        if (h>0) tmp[h-1]= atof(splitter.c_str());
        h++;
      }
      matrix[j]=new float[2];
      matrix[j][0]=tmp[0];
      matrix[j][1]=tmp[1];
      j++;
    }
   myfile.close();
   rows=j;
 }
 else {cout << "Unable to open file"; } 
 
 return matrix;
}


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

float ** matr_D(float ** m, float ** c, int centroids, int entries)
{
 float ** matr_D = new float * [centroids];
 for(int i=0;i<centroids;i++)
    matr_D[i]=new float [entries];
 
 for (int i=0;i<entries;i++)
   for (int h=0;h<centroids;h++)
     matr_D[h][i]=dist_eucl(c[h],m[i]);
 
 return matr_D; 
}

float ** matr_G(float ** m, int centroids, int rows)
{
 float ** matr_G = new float * [centroids];
 int max_i=0;
 int * clusters = new int[centroids];
 for (int i=0;i<centroids;i++)
    matr_G[i]=new float [rows];
 for(int i=0;i<centroids;i++)
      clusters[i]=0;

 for (int i=0;i<rows;i++)
  {
    max_i=0;
    for(int h=0;h<centroids;h++)
      {
        if(m[h][i]<m[max_i][i] && clusters[h]<CLUSTER_MAX_SIZE) max_i=h; // constraints to the max size of each cluster
        matr_G[h][i]=0;  
      }
    clusters[max_i]+=1;
    matr_G[max_i][i]=1;  

  }
 return matr_G; 
}

float * centroid(float ** start, float * G_sub, int rows)
{
 float * centroid=new float[2];
 centroid[0]=0;centroid[1]=0;
 int c=0;
 for (int i=0;i<rows;i++)
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

int G_diff(float ** A, float ** B, int centroids, int rows)
{
  for(int i=0;i<centroids;i++)
    for (int h=0;h<rows;h++)
    {
      if(A[i][h]!=B[i][h]) return 0;
    }
  return 1;
}

int main () {

  char * file="example.txt";
  int rows=0;
  float ** matrix=matrixGen(file, rows);
  /*for(int m=0;m<rows;m++)
    {
     cout << m << " ";    
     for(int n=0;n<2;n++)
      cout << matrix[m][n] << " " ;
     cout << '\n';
    }
  */
	
  float ** c=new float*[10];
  int centroids=10;
  cout << "Creating "<< centroids <<" centroids" << '\n';
  for(int i=0;i<centroids;i++)
    {
     c[i]=new float[2];
     c[i][0]=matrix[i][0];
     c[i][1]=matrix[i][1];
     cout << "C" << i << " " << c[i][0] << " - " << c[i][1] << '\n';
    }
  
  float ** D=matr_D(matrix,c,centroids,rows);
  float ** G=matr_G(D,centroids,rows);

  cout << "Matrix D" << '\n';
  for(int i=0;i<centroids;i++)
    {
     for(int h=0;h<rows;h++)
      cout << D[i][h] << " " ; 
     cout << '\n';
    }
  cout << "---------------------" << '\n';
  
  cout << "Matrix G" << '\n';
  for(int i=0;i<centroids;i++)
    {
     for(int h=0;h<rows;h++)
      cout << G[i][h] << " " ; 
     cout << '\n';
    }
  cout << "---------------------" << '\n';
  for(int i=0;i<centroids;i++)
    {
      c[i]=centroid(matrix,G[i],rows);   
      cout << "C" << i << " " << c[i][0] << " - " << c[i][1] << '\n';
    }
  cout << "---------------------" << '\n';
  
  
  /*--------------ITERATIVE----------------*/
  
  /*
  float ** matr_D(float ** m, float ** c, int centroids, int entries)
  float ** matr_G(float ** m, int centroids, int rows)
  G_diff(float ** A, float ** B, int centroids, int rows)
  */
  cout << "G_diff " << G_diff(G,matr_G(matr_D(matrix,c,centroids,rows),centroids,rows),centroids,rows) << '\n';

  while(G_diff(G,matr_G(matr_D(matrix,c,centroids,rows),centroids,rows),centroids,rows) ==0 )
  {
    D=matr_D(matrix,c,centroids,rows);
    G=matr_G(D,centroids,rows);
    cout << "Matrix D" << '\n';
    for(int i=0;i<centroids;i++)
    {
     for(int h=0;h<rows;h++)
      cout << D[i][h] << " " ; 
     cout << '\n';
    }
    cout << "---------------------" << '\n';
    cout << "Matrix G" << '\n';
    for(int i=0;i<centroids;i++)
     {
      for(int h=0;h<rows;h++)
      cout << G[i][h] << " " ; 
      cout << '\n';
     }
     cout << "---------------------" << '\n';
    for(int i=0;i<centroids;i++)
     {
      c[i]=centroid(matrix,G[i],rows);   
      cout << "C" << i << " " << c[i][0] << " - " << c[i][1] << '\n';
     }
    cout << "---------------------" << '\n';
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