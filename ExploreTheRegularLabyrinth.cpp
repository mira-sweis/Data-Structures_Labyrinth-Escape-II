// This file has no TO DOs because there is no code to write in this file.

#include <vector>
#include <map>
#include <sstream>
#include <set>
#include "maze.h"
#include "grid.h"
#include "EscapeTheLabyrinth.h"
using namespace std;


int main() {
	Maze m(4, 4);
    MazeCell* start = m.mazeFor(kYourName);
    
    // Put your break point here!
    
    if (isPathToFreedom(start, kPathOutOfRegularMaze)) {
    	cout << "You escaped!" << endl;
    } else {
    	cout << "You have not escaped!" << endl;
    }
    
    return 0;
}
