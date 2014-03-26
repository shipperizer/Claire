// reading a text file

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

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

int main () {
	char * file="example.txt";
	int rows=0;
	float ** matrix=matrixGen(file, rows);
    for(int m=0;m<rows;m++)
    	{
    	 cout << m << " ";	  
    	 for(int n=0;n<2;n++)
    		cout << matrix[m][n] << " " ;
    	 cout << '\n';
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