//
// grid.h
// CS251 Proj #4 By: Mira Sweis
// UIC Spring 2022
//
// This .h file is responsible for defining a class Grid<T>.
// Designed to support a C-style Array of linked lists.
//

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
 private:
  struct CELL {
    CELL* Next;
    T Val;
    size_t NumCols;  // total # of columns (0..NumCols-1)
    // defaults of struct CELL
    CELL(CELL* _Next = nullptr, T _Val = T(), size_t _NumCols = 0) {
      Next = _Next;
      Val = _Val;
      NumCols = _NumCols;
    }
  };

  size_t NumRows;  // total # of rows (0..NumRows-1)
  CELL** Rows;     // C array of linked lists

 public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 Grid.  All
  // elements are initialized to the default value of T.
  //
  Grid() {
    // initialize 4 rows
    Rows = new CELL*[4];
    NumRows = 4;

    // allocate the first cell of the linked list with default value:
    for (size_t r = 0; r < NumRows; ++r) {
        Rows[r] = new CELL(nullptr, T(), 4);
		CELL* cur = Rows[r];

        // create the linked list for this row.
        for (size_t c = 1; c < Rows[r]->NumCols; ++c) {
            cur->Next = new CELL(nullptr, T());
			cur = cur->Next;
        }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a Grid with R rows,
  // where each row has C columns. All elements are initialized to
  // the default value of T.
  // Copied from Grid(). Only change is size of rows(R).
  //
  Grid(size_t R, size_t C) {
    // constructs a grid with R rows
    if (R < 0 || C < 0) {
        throw out_of_range("r or c is <= zero");
    }
    
    // copied from Grid()
    Rows = new CELL*[R];
    NumRows = R;

    // allocate the first cell of the linked list with default value:
    for (size_t r = 0; r < NumRows; ++r) {
        Rows[r] = new CELL(nullptr, T(), C);
		CELL* cur = Rows[r];

        // create the linked list for this row.
        for (size_t c = 1; c < Rows[r]->NumCols; ++c) {
            cur->Next = new CELL(nullptr, T());
			cur = cur->Next;
        }
    }
  }

  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated by the vector.
  // Code mainly copied from Project Jumpstart (slide 14).
  //
  virtual ~Grid() {
      CELL* prev = nullptr;
        // transversing through rows
        for (size_t rows = 0; rows < NumRows; ++rows) {
            // set current CELL to the head
            CELL* cur = Rows[rows];
            while (cur != nullptr) {
                prev = cur;
                cur = cur->Next;
                delete prev;
            }
        }
        // delete rows
        delete[] Rows;
  }

  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a Grid that contains a
  // copy of an existing Grid.  Example: this occurs when passing
  // Grid as a parameter by value
  //
  //   void somefunction(Grid<int> G2)  <--- G2 is a copy:
  //   { ... }
  //
  Grid(const Grid<T>& other) {
      // declares new row with capacity of other
      this->Rows = new CELL*[other.NumRows];
      this->NumRows = other.NumRows;
      
      // stytle from Grid() 
      for (size_t r = 0; r < NumRows; ++r) {
          // column[0] for row[r] filled
          this->Rows[r] = new CELL(nullptr, other.Rows[r]->Val, other.Rows[r]->NumCols);
          CELL* cur = Rows[r];
          // this accesses column[1] for next...
          CELL* curOther = other.Rows[r]->Next;

          for (size_t c = 1; c < Rows[r]->NumCols; ++c) {
              cur->Next = new CELL(nullptr, curOther->Val);
              // incrementing both currents
              cur = cur->Next;
              curOther = curOther->Next;
          }
      }
  }

  //
  // copy operator=
  //
  // Called when you assign one vector into another, i.e. this = other;
  //
  Grid& operator=(const Grid& other) {
      // checks if are equal
      if (this == &other) {
          return *this;
      }
      // clears array first
      // copied from ~destructor
      CELL* prev = nullptr;
        for (size_t rows = 0; rows < NumRows; ++rows) {
            CELL* cur = Rows[rows];
            while (cur != nullptr) {
                prev = cur;
                cur = cur->Next;
                delete prev;
            }
        }
        delete[] Rows;

      // copy operation: from copyConstructor
      this->Rows = new CELL*[other.NumRows];
      this->NumRows = other.NumRows;
      for (size_t r = 0; r < NumRows; ++r) {
          this->Rows[r] = new CELL(nullptr, other.Rows[r]->Val, other.Rows[r]->NumCols);
          CELL* cur = Rows[r];
          CELL* curOther = other.Rows[r]->Next;

          for (size_t c = 1; c < Rows[r]->NumCols; ++c) {
              cur->Next = new CELL(nullptr, curOther->Val);
              cur = cur->Next;
              curOther = curOther->Next;
          }
      }
      return *this;
  }

  //
  // numrows
  //
  // Returns the # of rows in the Grid.  The indices for these rows
  // are 0..numrows-1.
  //
  size_t numrows() const {
      return NumRows;
  }

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  For now, each row will have the same number of columns.
  //
  size_t numcols(size_t r) const {
      return Rows[r]->NumCols;
  }

  //
  // size
  //
  // Returns the total # of elements in the grid.
  //
  size_t size() const {
      size_t size = 0;
      for (size_t r = 0; r < NumRows; ++r) {
          size += Rows[r]->NumCols; 
      }
      return size;
  }

  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    grid(r, c) = ...
  //    cout << grid(r, c) << endl;
  //
  T& operator()(size_t r, size_t c) {
      // checks for invalid entry
      if (r < 0 || c < 0 || r >= NumRows || c >= Rows[r]->NumCols) {
          throw out_of_range("Invalid Input: too small or too large.");
      }
      // for finding the index:
      size_t i = 0;
      CELL* cur = Rows[r];
      while (cur != nullptr) {
          // if finds value at index == c
          if (c == i)
              return cur->Val;
          i++;
          // iterates current till index found
          cur = cur->Next;
      } 
      return cur->Val;
  }

  //
  // _output
  //
  // Outputs the contents of the grid; for debugging purposes.  This is not
  // tested.
  //
  void _output() {
      // empty
  }

};
