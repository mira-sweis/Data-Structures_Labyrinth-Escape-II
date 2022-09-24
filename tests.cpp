//
// tests.cpp for CS251 Project #4
//
// By: Mira Sweis
// UIC Spring 2022
//
// This file is for testing the grid.h file functions and constructors.
// Also, for testing the isPathToFreedom function in EscapeTheLabyrinth.h file
//

#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include "maze.h"
#include "grid.h"
#include "EscapeTheLabyrinth.h"

// **size() is tested throught in a multitude of different tests and types**

// tests the default constructor
// always has size 16
TEST(grid, defaultConstructor) {
    Grid<int> g1;
    ASSERT_EQ(g1.size(), 16);

    Grid<char> g2;
    ASSERT_EQ(g1.size(), 16);
    
    Grid<string> g3;
    ASSERT_EQ(g1.size(), 16);
    
    Grid<double> g4;
    ASSERT_EQ(g1.size(), 16);
}

//
// tests for numCols
TEST(grid, numCols) {
    Grid<int> g1(100, 200);
    // tests column # for each row
    for (int i = 0; i < g1.numrows(); ++i) {
        ASSERT_EQ(g1.numcols(i), 200);
    }
    
    Grid<char> g2(100, 300);
    // tests column # for each row
    for (int i = 0; i < g1.numrows(); ++i) {
        ASSERT_EQ(g2.numcols(i), 300);
    }
    
    Grid<double> g3(300, 200);
    // tests column # for each row
    for (int i = 0; i < g1.numrows(); ++i) {
        ASSERT_EQ(g3.numcols(i), 200);
    }
    
    Grid<string> g4(300, 300);
    // tests column # for each row
    for (int i = 0; i < g1.numrows(); ++i) {
        ASSERT_EQ(g4.numcols(i), 300);
    }
}

//
// test for numrows
TEST(grid, numrows) {
    Grid<int> g1;
    ASSERT_EQ(g1.numrows(), 4);
    
    Grid<int> g2(20, 15);
    ASSERT_EQ(g2.numrows(), 20);
    
    Grid<double> g3;
    ASSERT_EQ(g3.numrows(), 4);
    
    Grid<double> g4(15, 15);
    ASSERT_EQ(g4.numrows(), 15);
    
    Grid<char> g5;
    ASSERT_EQ(g5.numrows(), 4);
    
    Grid<char> g6(5, 50);
    ASSERT_EQ(g6.numrows(), 5);
    
    Grid<string> g7;
    ASSERT_EQ(g7.numrows(), 4);
    
    Grid<string> g8(100, 15);
    ASSERT_EQ(g8.numrows(), 100);
}

//
// tests parameterized constructor of different grids
TEST(grid, parameterisedConstructorSize) {
    // creates grid with perameter
    Grid<int> g2(40, 15);
    // tests size
    ASSERT_EQ(g2.size(), 600);
    ASSERT_EQ(g2.numcols(0), 15);
    ASSERT_EQ(g2.numrows(), 40);
    
    // tests new grid by looping through every row
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            Grid<int> g2(i, j);
            ASSERT_EQ(g2.size(), i*j);
        }
    }

    // type char
    Grid<char> g4(20, 15);
    ASSERT_EQ(g4.size(), 300);
    ASSERT_EQ(g4.numcols(0), 15);
    ASSERT_EQ(g4.numrows(), 20);
    
    for (size_t i = 0; i < 70; ++i) {
        for (int j = 0; j < 70; ++j) {
            Grid<char> g2(i, j);
            ASSERT_EQ(g2.size(), i*j);
        }
    }
    
    // type string
    Grid<string> g6(300, 15);
    ASSERT_EQ(g6.size(), 4500);
    ASSERT_EQ(g6.numcols(0), 15);
    ASSERT_EQ(g6.numrows(), 300);
    
    for (size_t i = 0; i < 300; ++i) {
        for (int j = 0; j < 15; ++j) {
            Grid<string> g2(i, j);
            ASSERT_EQ(g2.size(), i*j);
        }
    }
    
    // type double
    Grid<double> g8(50, 40);
    ASSERT_EQ(g8.size(), 2000);
    ASSERT_EQ(g8.numcols(0), 40);
    ASSERT_EQ(g8.numrows(), 50);
    
    for (size_t i = 0; i < 50; ++i) {
        for (int j = 0; j < 40; ++j) {
            Grid<double> g2(i, j);
            ASSERT_EQ(g2.size(), i*j);
        }
    }

}

//
// tests perameterized constructor error throws
TEST(grid, parameterisedConstructorErrors) {
    try {
        Grid<int> g1(0, 2);
    } catch (exception& e) {
        string s(e.what());
        EXPECT_EQ(s, "r or c is <= zero");
    }
    
    try {
        Grid<string> g1(0, 40);
    } catch (exception& e) {
        string s(e.what());
        EXPECT_EQ(s, "r or c is <= zero");
    }
    
    try {
        Grid<char> g1(0, 0);
    } catch (exception& e) {
        string s(e.what());
        EXPECT_EQ(s, "r or c is <= zero");
    }
    
    try {
        Grid<double>g1(5, 0);
    } catch (exception& e) {
        string s(e.what());
        EXPECT_EQ(s, "r or c is <= zero");
    }
}

//
// tests copy constructor size
TEST(grid, copyConstructorSize) {
    Grid<int> g1(2, 2);
    Grid<int> g2(g1);
    
    ASSERT_EQ(g2.size(), 4);
    ASSERT_EQ(g2.numcols(0), 2);
    ASSERT_EQ(g2.numrows(), 2);
    
    Grid<char> g3(7, 20);
    Grid<char> g4(g3);
    
    ASSERT_EQ(g4.size(), 140);
    ASSERT_EQ(g4.numcols(0), 20);
    ASSERT_EQ(g4.numrows(), 7);
    
    Grid<double> g5(9, 9);
    Grid<double> g6(g5);
    
    ASSERT_EQ(g6.size(), 81);
    ASSERT_EQ(g6.numcols(0), 9);
    ASSERT_EQ(g6.numrows(), 9);
    
    Grid<string> g7(25, 6);
    Grid<string> g8(g7);
    
    ASSERT_EQ(g8.size(), 150);
    ASSERT_EQ(g8.numcols(0), 6);
    ASSERT_EQ(g8.numrows(), 25);
}

//
// tests copy constructor copying abilities
TEST(grid, copyConstructorCopy) {
    Grid<int> g5(15, 14);
    for (int i = 0; i < 15; ++i) {
        int n = rand() % 1000;
        for (int j = 0; j < 14; ++j) {
            g5(i, j) = n;
        }
    }
    // copy operation:
    Grid<int> g6(g5);
    ASSERT_EQ(g5.size(), g6.size());
    ASSERT_EQ(g5.numrows(), g6.numrows());
    ASSERT_EQ(g5.numcols(0), g6.numcols(0));
    ASSERT_EQ(g5(3, 2), g6(3, 2));
    // changing then testing
    // imposibble for the OG grid to have a negative number
    g6(1, 1) = -78;
    ASSERT_NE(g6(1, 1), g5(1, 1));
    
    //
    // new test type
    Grid<string> g7(200, 300);
    for (int i = 0; i < 200; ++i) {
        int n = rand() % 1000;
        string s = to_string(n);
        for (int j = 0; j < 300; ++j) {
            g7(i, j) = s;
        }
    }
    // copying operation:
    Grid<string> g8(g7);
    for (int i = 0; i < 200; ++i) {
        for (int j = 0; j < 300; ++j) {
            ASSERT_EQ(g8(i, j), g7(i, j));
        }
    }
    ASSERT_EQ(g8.size(), g7.size());
    ASSERT_EQ(g8.numrows(), g7.numrows());
    ASSERT_EQ(g8.numcols(0), g7.numcols(0));
    // changing the copy then comaring:
    // imposibble for the OG grid to have a negative number
    g8(20, 20) = "proj#4";
    ASSERT_NE(g8(20, 20), g7(20, 20));
    
    //
    // new test type
    Grid<double> g9(56, 40);
    for (int i = 0; i < 56; ++i) {
        double n = (double)rand() / 1000;
        for (int j = 0; j < 40; ++j) {
            g9(i, j) = n;
        }
    }
    // copy operation
    Grid<double> g10(g9);
    ASSERT_EQ(g9(9, 2), g10(9, 2));
    ASSERT_EQ(g9.size(), g10.size());
    ASSERT_EQ(g9.numrows(), g10.numrows());
    ASSERT_EQ(g9.numcols(0), g10.numcols(0));
    // changing cell then comparing
    g10(20, 20) = -4.9;
    ASSERT_NE(g10(20, 20), g9(20, 20));
    
    //
    // new test type
    Grid<char> g11(90,200);
    for (int i = 0; i < 90; ++i) {
        int n = rand() % 1000;
        for (int j = 0; j < 200; ++j) {
            g11(i, j) = n;
        }
    }
    // copy operation
    Grid<char> g12(g11);
    for (int i = 0; i < 90; ++i) {
        for (int j = 0; j < 200; ++j) {
            ASSERT_EQ(g11(i, j), g12(i, j));
        }
    }
    ASSERT_EQ(g11(50, 50), g12(50, 50));
    ASSERT_EQ(g11.size(), g12.size());
    ASSERT_EQ(g11.numrows(), g12.numrows());
    ASSERT_EQ(g11.numcols(0), g12.numcols(0));
    // changing a cell in one
    g12(30, 30) = 'E';
    ASSERT_NE(g11(30, 30), g12(30, 30));
}

//
// tests copy operator for size
TEST(grid, copyOperatorSize) {
    Grid<int> g1(5, 5);
    Grid<int> g2;
    g2 = g1;
    ASSERT_EQ(g2.size(), 25);
    
    Grid<string> g30(70, 56);
    Grid<string> g40;
    g40 = g30;
    ASSERT_EQ(g40.size(), 3920);
    
    Grid<double> g33(7, 7);
    Grid<double> g44;
    g44 = g33;
    ASSERT_EQ(g44.size(), 49);
    
    Grid<char> g32(70, 8);
    Grid<char> g42;
    g42 = g32;
    ASSERT_EQ(g42.size(), 560);
}

TEST(grid, copyOperatorCopyingThenChanging) {
    //
    // testing with integer
    //
    Grid<int> g11(90,100);
    Grid<int> g12(49,88);
    Grid<int> g13(90, 100);
    for (int i = 0; i < 90; ++i) {
        int n = rand() % 1000;
        for (int j = 0; j < 100; ++j) {
            g11(i, j) = n;
            // filling new grid later to test differences
            g13(i, j) = (2 * n);
        }
    }
    g12 = g11;
    for (int i = 0; i < 90; ++i) {
        for (int j = 0; j < 100; ++j) {
            ASSERT_EQ(g11(i, j), g12(i, j));
        }
    }
    ASSERT_EQ(g11.numrows(), g12.numrows());
    ASSERT_EQ(g11.numcols(3), g12.numcols(3));
    
    // now changing the grid to new different grid;
    g12 = g13;
    for (int i = 0; i < g12.numrows(); ++i) {
        for (int j = 0; j < g12.numcols(i); ++j) {
            // should not equl OG grid
            EXPECT_NE(g11(i, j), g12(i, j));
        }
    }
    
    //
    // now testing with char
    //
    Grid<char> g1(90,200);
    Grid<char> g2(49,88);
    Grid<char> g3(90, 200);
    for (int i = 0; i < 90; ++i) {
        int n = rand() % 1000;
        int s = rand() % 100;
        for (int j = 0; j < 200; ++j) {
            g1(i, j) = n;
            // filling new grid later to test differences
            g3(i, j) = s;
        }
    }
    g2 = g1;
    for (int i = 0; i < 90; ++i) {
        for (int j = 0; j < 200; ++j) {
            ASSERT_EQ(g1(i, j), g2(i, j));
        }
    }
    ASSERT_EQ(g1.numrows(), g2.numrows());
    ASSERT_EQ(g1.numcols(5), g2.numcols(5));
    
    // now changing the grid to new different grid;
    g2 = g3;
    for (int i = 0; i < g2.numrows(); ++i) {
        for (int j = 0; j < g2.numcols(i); ++j) {
            // should not equl OG grid
            EXPECT_NE(g1(i, j), g2(i, j));
        } 
    }
    
    //
    // now testing with double
    //
    Grid<double> g4(70,150);
    Grid<double> g5(49,88);
    Grid<double> g6(70, 150);
    for (int i = 0; i < 70; ++i) {
        double n = (double)rand() / 1000;
        for (int j = 0; j < 150; ++j) {
            g4(i, j) = n;
            // filling new grid later to test differences
            g6(i, j) = (3.0 * n);
        }
    }
    g5 = g4;
    // testing if all equal
    for (int i = 0; i < 70; ++i) {
        for (int j = 0; j < 150; ++j) {
            ASSERT_EQ(g4(i, j), g5(i, j));
        }
    }
    // testing numrows and numcols
    ASSERT_EQ(g4.numrows(), g5.numrows());
    ASSERT_EQ(g4.numcols(3), g5.numcols(3));
    
    // now changing the grid to new different grid;
    g5 = g6;
    for (int i = 0; i < g5.numrows(); ++i) {
        for (int j = 0; j < g5.numcols(i); ++j) {
            // should not equl OG grid
            EXPECT_NE(g4(i, j), g5(i, j));
        } 
    }
    
    //
    // now testing with string
    //
    Grid<string> g7(40, 40);
    Grid<string> g8(2, 3);
    Grid<string> g9(40, 40);
    for (int i = 0; i < 40; ++i) {
        int n = rand() % 1000;
        string s = to_string(n);
        for (int j = 0; j < 40; ++j) {
            g7(i, j) = s;
            g9(i, j) = s + "orange";
            g8 = g7;
            ASSERT_EQ(g7(i, j), g8(i, j));
        }
    }
    ASSERT_EQ(g7(3, 2), g8(3, 2));
    ASSERT_EQ(g7.numrows(), g8.numrows());
    ASSERT_EQ(g7.numcols(6), g8.numcols(6));
    
    // now changing the grid to new different grid;
    g8 = g9;
    for (int i = 0; i < g8.numrows(); ++i) {
        for (int j = 0; j < g8.numcols(i); ++j) {
            // should not equl OG grid
            EXPECT_NE(g7(i, j), g8(i, j));
        } 
    }
}

//
// tests the reference operator
TEST(grid, referenceOperator) {
    Grid<int> g1(50, 50);
    int arr[50][50];
    
    // goes through the grid and 2D array for matches
    for (int i = 0; i < 50; ++i) {
        int n = rand() % 1000;
        for (int j = 0; j < 50; ++j) {
            arr[i][j] = n;
            g1(i, j) = n;
            EXPECT_EQ(g1(i, j), arr[i][j]);
        }
    }
    Grid<string> g2(100, 100);
    string arr2[100][100];
    
    for (int i = 0; i < 100; ++i) {
        int n = rand() % 1000;
        string s = to_string(n);
        for (int j = 0; j < 100; ++j) {
            arr2[i][j] = n;
            g2(i, j) = n;
            EXPECT_EQ(g2(i, j), arr2[i][j]);
        }
    }
    
    Grid<double> g3(50, 50);
    double arr3[50][50];
    
    for (int i = 0; i < 50; ++i) {
        double n = rand() % 1000;
        string s = to_string(n);
        for (int j = 0; j < 50; ++j) {
            arr3[i][j] = n;
            g3(i, j) = n;
            EXPECT_EQ(g3(i, j), arr3[i][j]);
        }
    }
    
    Grid<char> g4(80, 120);
    char arr4[80][120];
    
    for (int i = 0; i < 80; ++i) {
        int n = rand() % 1000;
        string s = to_string(n);
        for (int j = 0; j < 120; ++j) {
            arr4[i][j] = n;
            g4(i, j) = n;
            EXPECT_EQ(g4(i, j), arr4[i][j]);
        }
    }
}

//
// tests possible input errors in reference operator
TEST(grid, referenceOperatorSize) {
    Grid<int> g1(5, 5);
    //tries a value equal to size
    try {
        g1(5, 5);
    } catch (exception& e) {
        string s(e.what());
        EXPECT_EQ(s, "Invalid Input: too small or too large.");
    }
    // tries negative numbers
    Grid<char> g2(50, 50);
    try {
        g2(70, -3);
    } catch (exception& e) {
        string s(e.what());
        EXPECT_EQ(s, "Invalid Input: too small or too large.");
    }
    
    Grid<string> g3(20, 30);
    try {
        g3(0, 30);
    } catch (exception& e) {
        string s(e.what());
        EXPECT_EQ(s, "Invalid Input: too small or too large.");
    }
    // the following will loop in valid perameters for a while
    // once it exceeds correct perameters it should check for exeptions
    // then I compare the # of exceptions to the theoretical number.
    int count = 0;
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            try {
                // tries accessing cells
                g3(i, j);
            } catch (exception& e) {
                string s(e.what());
                EXPECT_EQ(s, "Invalid Input: too small or too large.");
                count++;
            }
        }
    }
    // checks to see if amount of exceptions caught were correct
    ASSERT_EQ(count, 300);
    
    // tries negative numbers for type double
    Grid<double> g4(15, 25);
    try {
        g4(-5, 0);
    } catch (exception& e) {
        string s(e.what());
        EXPECT_EQ(s, "Invalid Input: too small or too large.");
    }
    // to check number of exceptions caught
    // same as above loop just different type
    int count2 = 0;
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            try {
                // tries to access cells
                g4(i, j);
            } catch (exception& e) {
                string s(e.what());
                EXPECT_EQ(s, "Invalid Input: too small or too large.");
                count2++;
            }
        }
    }
    // checks to see if amount of exeptions caught were correct
    ASSERT_EQ(count2, 525);
}

//
// tests operato() when changing manually
TEST(grid, testSetterGetter) {
    Grid<int> g1(50, 50);
    // fill grid with stuff
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            g1(i, j) = i*j;
            ASSERT_EQ(g1(i, j), i*j);
        }
    }
    g1(3, 3) = 766;
    ASSERT_EQ(g1(3, 3), 766);
    
    //
    // new type test
    Grid<double> g2(50, 50);
    // fill grid with stuff
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            double n = i*j;
            g2(i, j) = n;
            ASSERT_EQ(g2(i, j), i*j);
        }
    }
    g2(45, 45) = 70.9;
    ASSERT_EQ(g2(45, 45), 70.9);
    
    //
    // new test type
    Grid<char> g3(50, 50);
    // fill grid with stuff
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            g3(i, j) = i;
            ASSERT_EQ(g3(i, j), i);
        }
    }
    g3(30, 40) = 'A';
    ASSERT_EQ(g3(30, 40), 'A');
    
    //
    // new type test
    Grid<string> g4(50, 50);
    // fill grid with stuff
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            string s = to_string(i*j);
            g4(i, j) = s;
            ASSERT_EQ(g4(i, j), s);
        }
    }
    g4(20, 25) = "orange";
    ASSERT_EQ(g4(20, 25), "orange");
}

// Provided Test: sample maze from handout, make lots more yourself!
TEST(maze, basic) {
    vector<string> textMaze;

    textMaze.push_back("* *-W *");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-* * *");
    textMaze.push_back("  | | |");
    textMaze.push_back("S *-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-*-* P");

    Maze m(textMaze);

    MazeCell* start = m.getStart(2, 2);

    /* These paths are the ones in the handout. They all work. */
    EXPECT_TRUE(isPathToFreedom(start, "ESNWWNNEWSSESWWN"));
    EXPECT_TRUE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES"));
    EXPECT_TRUE(isPathToFreedom(start, "WNNEWSSESWWNSEENES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT_FALSE(isPathToFreedom(start, "ESNW"));
    EXPECT_FALSE(isPathToFreedom(start, "SWWN"));
    EXPECT_FALSE(isPathToFreedom(start, "WNNE"));

    /* These paths don't work, since they aren't legal paths. */
    EXPECT_FALSE(isPathToFreedom(start, "WW"));
    EXPECT_FALSE(isPathToFreedom(start, "NN"));
    EXPECT_FALSE(isPathToFreedom(start, "EE"));
    EXPECT_FALSE(isPathToFreedom(start, "SS"));
}

// Provided Test: don't allow going through walls
TEST(maze, tryingToGoThroughWalls) {
    vector<string> textMaze;

    textMaze.push_back("* S *");
    textMaze.push_back("     ");
    textMaze.push_back("W * P");
    textMaze.push_back( "     ");
    textMaze.push_back( "* * *");

    Maze m(textMaze);

    MazeCell* start = m.getStart(1, 1);

    EXPECT_FALSE(isPathToFreedom(start, "WNEES"));
    EXPECT_FALSE(isPathToFreedom(start, "NWSEE"));
    EXPECT_FALSE(isPathToFreedom(start, "ENWWS"));
    EXPECT_FALSE(isPathToFreedom(start, "SWNNEES"));
}

// Provided Test: Works when starting on an item
TEST(maze, startOnItem) {
    vector<string> textMaze;

    textMaze.push_back("P-S-W");

    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);

    EXPECT_TRUE(isPathToFreedom(start, "EE"));
    start = m.getStart(0, 1);
    EXPECT_TRUE(isPathToFreedom(start, "WEE"));
    start = m.getStart(0, 2);
    EXPECT_TRUE(isPathToFreedom(start, "WW"));

}

// Provided Test: Reports errors if given illegal characters.
TEST(maze, invalidChar) {
    vector<string> textMaze;

    textMaze.push_back("* *-W *");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-* * *");
    textMaze.push_back("  | | |");
    textMaze.push_back("S *-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-*-* P");
    
    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);

    /* These paths contain characters that aren't even close to permissible. */
    EXPECT_FALSE(isPathToFreedom(start, "Q"));
    EXPECT_FALSE(isPathToFreedom(start, "X"));
    EXPECT_FALSE(isPathToFreedom(start, "!"));
    EXPECT_FALSE(isPathToFreedom(start, "?"));

    EXPECT_FALSE(isPathToFreedom(start, "n"));
    EXPECT_FALSE(isPathToFreedom(start, "s"));
    EXPECT_FALSE(isPathToFreedom(start, "e"));
    EXPECT_FALSE(isPathToFreedom(start, "w"));

    ///* These are tricky - they're legal paths that happen to have an unexpected
    // * character at the end.
    start = m.getStart(2, 2);
    EXPECT_FALSE(isPathToFreedom(start, "ESNWWNNEWSSESWWNQ"));
    EXPECT_FALSE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES!!!"));
    EXPECT_FALSE(isPathToFreedom(start, "WNNEWSSESWWNSEENES??"));

}

// Provided Test: This tests your personalized regular maze to see if you were
// able to escape.
TEST(maze, escapeRegularMaze) {
    Maze m(4, 4);
    MazeCell* start = m.mazeFor(kYourName);
    EXPECT_TRUE(isPathToFreedom(start, kPathOutOfRegularMaze));
}

// Provided Test: This tests your personalized twisty maze to see if you were
// able to escape.
TEST(maze, escapeTwistyMaze) {
    Maze m(4, 4);
    MazeCell* start = m.twistyMazeFor(kYourName);
    EXPECT_TRUE(isPathToFreedom(start, kPathOutOfTwistyMaze));
}

//
// new maze tests by student
//

// tests square maze
TEST(maze, newBasic1) {
    vector<string> textMaze;

    // 4x4 maze
    textMaze.push_back("* P-*-*");
    textMaze.push_back("  | | |");
    textMaze.push_back("*-* *-*");
    textMaze.push_back("  | |  ");
    textMaze.push_back("*-*-W *");
    textMaze.push_back("| |   |");
    textMaze.push_back("S-*-*-*");

    Maze m(textMaze);

    MazeCell* start = m.getStart(2, 0);
    
    // all 3 are correct routes to all
    EXPECT_TRUE(isPathToFreedom(start, "SENNNEESWS"));
    EXPECT_TRUE(isPathToFreedom(start, "SNEENENWW"));
    EXPECT_TRUE(isPathToFreedom(start, "EENENWWSSSW"));
    
    // correct toute but invalid charachters at the end
    EXPECT_FALSE(isPathToFreedom(start, "SENNNEESWS!!"));
    // invalid entry
    EXPECT_FALSE(isPathToFreedom(start, "f"));
    // goes through wall
    EXPECT_FALSE(isPathToFreedom(start, "EESWEESEN"));
}

//
// tests non square Maze
TEST(maze, newBasic2) {
    vector<string> textMaze;
    
    // 4x6 maze: starts at (0, 0)
    // starts on object and ends on an object
    textMaze.push_back("S-* * *");
    textMaze.push_back("| | |  ");
    textMaze.push_back("* *-W *");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-* *-*");
    textMaze.push_back("  |   |");
    textMaze.push_back("*-* *-*");
    textMaze.push_back("  | |  ");
    textMaze.push_back("*-* *-*");
    textMaze.push_back("    | |");
    textMaze.push_back("* *-*-P");
    
    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);
    
    // correct paths out
    EXPECT_TRUE(isPathToFreedom(start, "ESESESWSSE"));
    EXPECT_TRUE(isPathToFreedom(start, "ESENSSESWSES"));
    
    // incorrect paths
    EXPECT_FALSE(isPathToFreedom(start, "ESESESWSSW"));
    EXPECT_FALSE(isPathToFreedom(start, "SSESW"));
    // incorrect entry
    EXPECT_FALSE(isPathToFreedom(start, "ESESESW#S'W"));
}


