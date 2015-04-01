/*

 **************************
 * To intrepid Googlers: *
 **************************

 This file was written by Erik Swan for the Spring 2015 section of ECE 264.

 Although I have made it available publicly under the MIT license, you should be
 well aware that submitting *any* portion of this code as your own work is
 academically dishonest.

 Considering that this file and the corresponding GitHub project have been
 indexed by Google and are likely to show up among the top results for "ECE 264",
 you should assume that using any of this code will quite easily be flagged by
 the anti-cheating tools the teaching team likely has in place.

 Don't be dumb. Do your work.

*/

#include "answer06.h"
#include <stdio.h>

void traverseMaze(char ** maze, int x, int y, int w, int h, char direction) {
    int moveCount = 1;

    // Helper function to return opposite direction
    char oppositeDirection() {
        switch(direction) {
            case 'N':
                return 'S';
            case 'S':
                return 'N';
            case 'W':
                return 'E';
            default: // E
                return 'W';
        }
    }

    // Whether we are at a junction or not.
    int atJunction() {
        if(direction == 'S' || direction == 'N') {
            return maze[y][x-1] == ' ' || maze[y][x+1] == ' ';
        } else {
            // Assumed E or W direction
            return maze[y+1][x] == ' ' || maze[y-1][x] == ' ';
        }
    }

    // Force inline to avoid making call stack even deeper
    inline void traverseJunctions() {
        // Traverse West
        if(direction == 'S' || direction == 'N' || direction == 'W') {
            if(maze[y][x-1] == ' ') {
                traverseMaze(maze, x-1, y, w, h, 'W');
            }
        }

        // Traverse East
        if(direction == 'S' || direction == 'N' || direction == 'E') {
            if(maze[y][x+1] == ' ') {
                traverseMaze(maze, x+1, y, w, h, 'E');
            }
        }

        // Traverse North
        if(direction == 'W' || direction == 'E' || direction == 'N') {
            if(maze[y-1][x] == ' ' && y-1 > 0) {
                // Special case here, don't traverse into starting square
                traverseMaze(maze, x, y-1, w, h, 'N');
            }
        }

        // Traverse South
        if(direction == 'W' || direction == 'E' || direction == 'S') {
            if(maze[y+1][x] == ' ') {
                traverseMaze(maze, x, y+1, w, h, 'S');
            }
        }
    }

    // Whether we are at a dead-end
    int atDeadEnd() {
        switch(direction) {
            case 'N':
                return y-1 < 0 || maze[y-1][x] == 'X';
            case 'S':
                return y+1 >= h || maze[y+1][x] == 'X';
            case 'W':
                return x-1 < 0 || maze[y][x-1] == 'X';
            default: // E
                return x+1 >= w || maze[y][x+1] == 'X';
        }
    }

    // Advance down this branch
    void advanceBranch() {
        moveCount++;
        switch(direction) {
            case 'N':
                y--;
                break;
            case 'S':
                y++;
                break;
            case 'W':
                x--;
                break;
            default: // E
                x++;
        }
    }

    // Check if we've reached an intersection (junction)
    while(!(atJunction() || atDeadEnd())) {
        advanceBranch();
    }

    // Print descending instruction
    printf("%c %d\n", direction, moveCount);

    if(atJunction()) {
        traverseJunctions();
    }

    // Print ascending instruction
    printf("%c %d\n", oppositeDirection(), moveCount);
}

void print_directions(char** maze, int w, int h) {
    int x = (w/2)|1;
    int y = 1;
    char direction = 'S';

    // Traverse maze
    traverseMaze(maze, x, y, w, h, direction);
}
