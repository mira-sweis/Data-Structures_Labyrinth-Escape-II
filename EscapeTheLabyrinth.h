//
// EscapeTheLabyrinth.h
//
// CS251 Project #4
// By: Mira Sweis
// UIC Spring 2022
//
// This file is responsible for finding the solutions to the labyrinths.
// Specifically, implementing isPathToFreedom.
// There is on helper function defined for finding special characters.

#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

/* Change this constant to contain your full first and last name (middle is ok too).
 *
 * WARNING: Once you've set set this constant and started exploring your maze,
 * do NOT edit the value of kYourName. Changing kYourName will change which
 * maze you get back, which might invalidate all your hard work!
 */
const string kYourName = "Mira Sweis";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "ESESSENNNW";
const string kPathOutOfTwistyMaze = "SSSWNWWSS";

//
// helper function for checking if there is a character in the cell
//
void checkWhatsHere(MazeCell* &cur, bool& Potion, bool& Spellbook, bool& Wand) {
    if (cur->whatsHere == "Potion") {
        Potion = true;
    }
    if (cur->whatsHere == "Wand") {
        Wand = true;
    }
    if (cur->whatsHere == "Spellbook") {
        Spellbook = true;
    }
}

// finds path to end
bool isPathToFreedom(MazeCell *start, const string& moves) {
    MazeCell* cur = start;
    bool Potion = false; bool Wand = false; bool Spellbook = false;
    
    for (auto &x : moves) {
        // checks if moves are valid or not
        if (x != 'S' && x != 'N' && x != 'W' && x != 'E') {
            return false;
        }
        
        // checks for special charachter
        checkWhatsHere(cur, Potion, Spellbook, Wand);
        if (x == 'S') {
            cur = cur->south;
        } else if (x == 'N') {
            cur = cur->north;
        } else if (x == 'E') {
            cur = cur->east;
        } else if (x == 'W') {
            cur = cur->west;
        }
        if (cur == nullptr) {
            return false;
        }
    }
    // checks for special charachter one last time.
    checkWhatsHere(cur, Potion, Spellbook, Wand);
    // now sees if all three objects are found
    if (Spellbook && Wand && Potion) {
        return true;
    } else {
        return false;
    }
}
