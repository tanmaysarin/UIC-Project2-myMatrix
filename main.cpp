/*mymatrix.h*/

// 
// << TANMAY SARIN >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #02
//

//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#include <iostream>
#include <fstream>
#include <string>

#include "mymatrix.h"

using namespace std;

int main(){
    
    // Comment or uncomment the code to check the function...The basic ones are already uncommented to check initial
    // tests until matrix multiplication...
    
    mymatrix <int> m(12,6);
    mymatrix <int> m2;
//     mymatrix <int> m3;
//     mymatrix <int> result(4,4);
    
//     cout<<endl;
//     m(0, 0) = 123;
//     m(1, 1) = 456;
//     m(2, 2) = 789;
//     m(3, 3) = -99;
    
//     m._output();
//     cout<<endl;
//     cout<<"The number of rows are: "<<m.numrows()<<endl;
//     //cout<<"The number of cols are: "<<m.numcols(4)<<endl;
//     cout<<endl;
    
//     m2(0, 0) = 123;
//     m2(1, 1) = 456;
//     m2(2, 2) = 789;
//     m2(3, 3) = -99;
//     m2(3, 4) = 1;

//   m2._output();
    
//     cout<<"Growing number of columns here now :" <<endl;
//     m.growcols(4,7);
//     cout<<endl;
//     m._output();
//     cout<<endl;
//     cout<<endl;
//     cout<<"The number of rows after using the \"growcols\"  are: "<<m.numcols(4)<<endl;
//     cout<<endl;
    
//     cout<<"Growing the 2D vector now : "<<endl;
//     m.grow(8,8);
//     cout<<endl;
//     m._output();
    
//     cout<<"--------"<<endl;
    
//     m.size();
//     cout<<"The size is : "<<m.size()<<endl;

    
//     //m.at(0,3) = 5;
        
//     m._output();
    
//     cout<<endl;
//     cout<<"Scalar Multiplication now..."<<endl;
    
//     result = m * 2;
    
//     cout<<endl;
    
//     result._output();
    
//     cout<<endl;
    
//     cout<<"Trying the matrix multiplication here..."<<endl;

//     m3 = m * m2;
    
//     m3._output();
    
    
    m.growcols(0,16);
   // m._output();
    
    m.growcols(11,16);
   // m._output();
    
    int R = 12;
  int C = 6;
 
  for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
      m(r, c) = 10 * (r * 16 + c + 1);
 
  m(0, 14) = 123;
  m(0, 15) = 456;
  m(11, 10) = 789;
 
  m2 = m * 10;
    
    m2._output();
    
    cout<<m2.numrows()<<endl;
    cout<<m2.size()<<endl;
    
    return 0;
}
