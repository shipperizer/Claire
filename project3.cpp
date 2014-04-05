// reading a text file

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;
const int CLUSTER_MAX_SIZE=200;

double ** matrixGen(char * filename, int &rows)
{
  cout << "Be sure that the file has no more than 5000 rows" << '\n'; 
  string line;
  string splitter="";
  rows=0;
  double ** matrix=new double *[5000];
  ifstream myfile (filename);

  if (myfile.is_open())

  {
    int i=0,h=0,j=0;
    double * tmp=new double[3];//(x,y,capacity)
    while ( getline (myfile,line) && j<5000 )
    { 
      i=0;h=0;
      while(i<line.length() && h<4)
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
      matrix[j]=new double[3];
      matrix[j][0]=tmp[0];
      matrix[j][1]=tmp[1];
      matrix[j][2]=tmp[2];//Capacity
      j++;
    }
   myfile.close();
   rows=j;
 }
 else {cout << "Unable to open file"; } 
 
 return matrix;
}

double dist_eucl( double *a, double *b)
{
  double dist = (double)sqrt(pow((a[0]-b[0]),2)+pow((a[1]-b[1]),2));
  return dist;
}

double ** matr_D(double ** m, double ** c, int centroids, int entries)
{
 double ** matr_D = new double * [centroids];
 for(int i=0;i<centroids;i++)
    matr_D[i]=new double [entries];
 
 for (int i=0;i<entries;i++)
   for (int h=0;h<centroids;h++)
     matr_D[h][i]=dist_eucl(c[h],m[i]);
 
 return matr_D; 
}

double ** matr_G(double ** m, double ** starting, int centroids, int rows, double ** capacity)
{
 double ** matr_G = new double * [centroids];
 int max_i=0;
 double * clusters = new double[centroids];
 for (int i=0;i<centroids;i++)
    matr_G[i]=new double [rows];
 for(int i=0;i<centroids;i++)
      clusters[i]=0;

 for (int i=0;i<rows;i++)
  {
    max_i=0;  
    for(int h=0;h<centroids;h++)
      {
        if(m[h][i]<m[max_i][i] && clusters[h]+starting[i][2]<CLUSTER_MAX_SIZE) max_i=h; // constraints to the max size of each cluster
        matr_G[h][i]=0;  
      }

    if(clusters[max_i]+starting[max_i][2]<CLUSTER_MAX_SIZE)
      {
        clusters[max_i]+=starting[max_i][2];
        matr_G[max_i][i]=1;  
      }
  }
 *capacity= clusters;
 return matr_G; 
}

double * centroid(double ** start, double * G_sub, int rows)
{
 double * centroid=new double[2];
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
 if (c==0) c=1; // avoid -nan 
 centroid[0]/=c;
 centroid[1]/=c;
 return centroid;  
}

int G_diff(double ** A, double ** B, int centroids, int rows)
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
  double ** matrix=matrixGen(file, rows);
  double ** c=new double*[10];
  int centroids=10;
  double * capacities=0;
  cout << "Creating "<< centroids <<" centroids" << '\n';
  for(int i=0;i<centroids;i++)
    {
     c[i]=new double[2];
     c[i][0]=matrix[i][0];
     c[i][1]=matrix[i][1];
     cout << "C" << i << " " << c[i][0] << " - " << c[i][1] << '\n';
    }
  
  double ** D=matr_D(matrix,c,centroids,rows);
  double ** G=matr_G(D,matrix,centroids,rows,&capacities);
  for(int i=0;i<centroids;i++)
    cout << i << " capacities:  " << capacities[i] << '\n';
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
      cout << "C" << i << " " << c[i][0] << " - " << c[i][1];
      cout << " ----  Associated Cluster Capacity " << capacities[i] <<'\n';
    }
  cout << "---------------------" << '\n';
  
  
  /*--------------ITERATIVE----------------*/
  
  /*
  double ** matr_D(double ** m, double ** c, int centroids, int entries)
  double ** matr_G(double ** m, int centroids, int rows)
  G_diff(double ** A, double ** B, int centroids, int rows)
  */
  cout << "G_diff " << G_diff(G,matr_G(matr_D(matrix,c,centroids,rows),matrix,centroids,rows,&capacities),centroids,rows) << '\n';

  while(G_diff(G,matr_G(matr_D(matrix,c,centroids,rows),matrix,centroids,rows,&capacities),centroids,rows) ==0 )
  {
    D=matr_D(matrix,c,centroids,rows);
    G=matr_G(D,matrix,centroids,rows,&capacities);
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
      cout << "C" << i << " " << c[i][0] << " - " << c[i][1] << " ----  Associated Cluster Capacity " << capacities[i] << '\n';
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