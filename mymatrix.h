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

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>
class mymatrix
{
private:
  struct ROW
  {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All 
  // elements are initialized to the default value of T.
  //
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows, 
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  mymatrix(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::constructor: # of cols");

    //
    // TODO
    //
    Rows = new ROW[R];  // an array with user-specified R ROW structs:
    NumRows = R;
    
    // initialize each row to have user-specified C columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[C];  // an array with user-specified C elements of type T:
      Rows[r].NumCols = C;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }


  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a 
  // copy of an existing matrix.  Example: this occurs when passing 
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other)
  {

    this->Rows = new ROW[other.NumRows];
    this->NumRows = other.NumRows;
    
    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
    
      this->Rows[r].Cols = new T[other.Rows[r].NumCols];
      this->Rows[r].NumCols = other.Rows[r].NumCols;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        //Rows[r].Cols[c] = T{};  // default value for type T
        this->Rows[r].Cols[c] = other.Rows[r].Cols[c];  // default value for type T:
      }
    }
  }


  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const
  {
    return NumRows;
  }
  

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different 
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int r) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::numcols: row");

    return Rows[r].NumCols;
  }


  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains 
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value 
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int r, int C)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");

    T* temp = new T[C];
    if(Rows[r].NumCols < C){
        for(int i=0; i < C; ++i){
            if(i < Rows[r].NumCols){
                temp[i] = this->Rows[r].Cols[i]; //Copying existing elements to the new column
            }else{
                temp[i] = T{}; //Assigning default value of 0
            }
        }
        this->Rows[r].Cols = temp; //Assign the columns to the temp pointer..
        this->Rows[r].NumCols = C; //Assign the new number of columns in the matrix to C..
    }
  }


  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  // 
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to 
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  // 
  void grow(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::grow: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::grow: # of cols");
      
    if(NumRows < R){ //If the number of rows of the original matrix is less than the required number of rows...
        //int newNumRows = int NumRows + 1;
        ROW* tempRows = new ROW[R];
        for(int i=0; i < R; i++){
            if(i < NumRows){ //If there is any data to copy from the original matrix to the new matrix...
                int newColSize = C;
                int CurrColSize = this->Rows[i].NumCols;
                if(CurrColSize > newColSize){ // If the number of columns in the original matrix is more than the number of required columns 
                    newColSize = CurrColSize;
                }
                else{// If the number of columns in the original matrix is less than the number of required columns...
                    tempRows[i].Cols = new T[newColSize]; //Initializing a new array with the new column size...
                    tempRows[i].NumCols = newColSize; //Initializing the new size of the column to the original column...
                    for(int a = 0; a < newColSize; a++){ //Copying the data...
                        if(a < CurrColSize){
                            tempRows[i].Cols[a] = this->Rows[i].Cols[a];
                        }else{ //For new places...
                            tempRows[i].Cols[a] = T{};
                        }
                    }
                }
            }else{ //If there is no data to copty to the new matricx form the original matrix...
                tempRows[i].Cols = new T[C];
                tempRows[i].NumCols = C;
                for(int j=0; j < C; j++){
                    tempRows[i].Cols[j] = T{};
                }
            }
        }
        Rows = tempRows;
        NumRows = R;
    }else{ // If the number of the rows of the original matrix is equal to or more than the required number of rows...
        for(int k = 0; k < NumRows; k++){
            if(Rows[k].NumCols<C){
                this->growcols(k,C);
            }
        }
    }
  }


  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //
  int size() const
  {
    int total = 0;
    
    for(int i = 0; i < NumRows; ++i){
            total = total + Rows[i].NumCols;
    }
    return total;
  }


  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //
  T& at(int r, int c)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::at: row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::at: col");

    return Rows[r].Cols[c];
  }


  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T& operator()(int r, int c)
  {
    if (r < 0 || r >= NumRows){
        cout<<r<<endl;
      throw invalid_argument("mymatrix::(): row");}
    if (c < 0 || c >= Rows[r].NumCols){
        cout<<c<<endl;
      throw invalid_argument("mymatrix::(): col");}

    return Rows[r].Cols[c];
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar)
  {
    int count = 1;
    mymatrix<T> result(NumRows,count);
    
    for(int i=0; i<NumRows; ++i){
        for(int j=0; j<Rows[i].NumCols; ++j){
            result.growcols(i,Rows[i].NumCols);
            result.at(i,j) = Rows[i].Cols[j] * scalar;
        }
    }
    
    return result;
  }


  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  //
  //  
    
  //
  // both matrices must be rectangular for this to work:
  //
  mymatrix<T> operator*(const mymatrix<T>& other)
  {
    //Check the number of columns in the first row, with that of all the rows..
    for(int i=0; i < other.numrows(); ++i){ //for the other matrix
        for(int j = 0; j < (other.numrows()); ++j){
            if(other.Rows[i].NumCols == other.Rows[j].NumCols){
            }else{
                throw runtime_error("mymatrix::*: other not rectangular");
                break;
            }
        }
        break; //Cause you only need to check once...
    }
    
    mymatrix<T> result(NumRows, other.Rows[0].NumCols);
    
    //Check the number of columns in the first row, with that of all the rows..    
    for(int i=0; i < numrows(); ++i){ // for the main matrix..
        for(int j = 0; j < numrows(); ++j){
            if(Rows[i].NumCols == Rows[j].NumCols){
            }else{
                throw runtime_error("mymatrix::*: this not rectangular");
                break;
            }
        }
        break; //Cause you only need to check once...
    }

    //
    // Okay, both matrices are rectangular.  Can we multiply?  Only
    // if M1 is R1xN and M2 is NxC2.  This yields a result that is
    // R1xC2.
    // 
    // Example: 3x4 * 4x2 => 3x2
    //
    for(int r= 0; r < NumRows; ++r){
        if(Rows[r].NumCols == other.numrows()){
            break;
        }else{
            throw runtime_error("mymatrix::*: size mismatch");
        }
    }

    //
    // Okay, we can multiply:
    //

    for(int r=0; r < NumRows; ++r){ //Number of rows in the main matrix...
    int colCounter = 0;
    here:
        int r2 = 0;
        result(r, colCounter) = 0;
        for(int c=0; c < Rows[r].NumCols; ++c){
            
            result(r, colCounter) = (Rows[r].Cols[c] * other.Rows[r2].Cols[colCounter]) + result(r, colCounter);    
            r2++; // Go to the next row in the second matrix..
        }
        
        while(colCounter <= (other.numcols(r) - 1)){
            ++colCounter;
            if(colCounter == other.numcols(r)){
                break;
            }
            goto here;
        }
    }
    return result;
  }

  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};
