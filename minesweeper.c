/* --- minesweeper.h --- */
#ifndef AALTO_MINESWEEPER_H
#define	AALTO_MINESWEEPER_H

typedef enum {
    UNKNOWN_FREE,
    UNKNOWN_MINE,
    KNOWN_FREE,
    KNOWN_MINE
} State;

typedef struct {
    unsigned int xsize, ysize;
    State **places;
} Field;

Field *createField(unsigned int xsize, unsigned int ysize);

void printField(const Field *f);

void deployMines(Field *f, unsigned int mines);

int checkPlace(const Field *f, unsigned int x, unsigned int y);

int countNeighbours(const Field *f, unsigned int x, unsigned int y);

#endif	/* AALTO_MINESWEEPER_H */
//-----------------------------------------------------------------------------------------------

/* --- minesweeper.c --- */
#include <stdlib.h>
#include "minesweeper.h"

/* Print the current state of the field */
void printField(const Field *f)
{
    unsigned int i, j, n;
    for (i = 0; i < f->ysize; i++) {
        for (j = 0; j < f->xsize; j++) {
            char c = '.';
            switch (f->places[i][j]) {
                case UNKNOWN_FREE:
                case UNKNOWN_MINE:
                    c = '?';
                    break;
                    
                case KNOWN_MINE:
                    c = '*'; break;
                    
                case KNOWN_FREE:
                    c = countNeighbours(f, j, i)+'0';
                    if(c == '0')
                        c = '.';
                    break;
            }
            printf("%c ", c);
        }
        printf("\n");
    }
}


/* Deploy mines to random locations in the given field
 * 
 * Parameters:
 * f: Minefield that has been created earlier
 * mines: number of mines to be deployed */
void deployMines(Field *f, unsigned int mines)
{
    unsigned int i;
    for (i = 0; i < mines; i++) {
        int x, y;
        do {
            x = rand() % f->xsize;
            y = rand() % f->ysize;
        } while(f->places[y][x] != UNKNOWN_FREE);
        f->places[y][x] = UNKNOWN_MINE;
    }
}


/* Create new field with given dimensions
 * Parameters:
 * xsize: horizontal size of the field
 * ysize: vertical size of the field
 * Returns:
 * Pointer to the newly allocated minefield */
Field *createField(unsigned int xsize, unsigned int ysize){
    Field *field = (Field*)malloc(ysize * sizeof(State*));
    field->places = malloc(ysize * sizeof(State*));
    if(!field)
        return NULL;
    for(unsigned int i = 0; i < ysize; i++)
        field->places[i] = malloc(xsize * sizeof(State*));
    for(unsigned int i = 0; i < ysize; i++){
        for(unsigned int j = 0; j < xsize; j++){
            field->places[i][j] = UNKNOWN_FREE;
            }
        }
    field->xsize = xsize;
    field->ysize = ysize;
    return field;
}

/* Checks the status of given location. At the same time, change the
 * status from UNKNOWN_MINE to KNOWN_MINE, or UNKNOWN_FREE to KNOWN_FREE
 * Parameters:
 * f: Minefield that has been allocated earlier
 * x, y: the coordinates of the place to be checked
 * Returns:
 * 1 if there was a mine; 0 if the location was free; -1 if given
 * coordinates are out of bounds */
int checkPlace(const Field *f, unsigned int x, unsigned int y){
    if(y > f->ysize || x > f->xsize)
            return -1;
    if(f->places[y][x] == UNKNOWN_MINE){
        f->places[y][x] = KNOWN_MINE;
        return 1;
    }
    else if(f->places[y][x] == UNKNOWN_FREE){
        f->places[y][x] = KNOWN_FREE;
        return 0;
    }  
}

/* Count how many of the neighboring locations have mines.
 * Parameters:
 * f: pointer to the field allocated earlier
 * x, y: coordinates of the place to be checked
 * 
 * Returns:
 * Number of mines in the neighborhood. At maximum there are 8 neighboring
 * locations. */
int countNeighbours(const Field *f, unsigned int x, unsigned int y){
    int count = 0;
    for(int i = -1; i <= 1; i++) { 
        if(((int)y + i < 0) || (y + i >= f->ysize)) { 
            continue;
        }
        for(int j = -1; j <= 1; j++) {
            if(((int)x + j < 0) || (x + j >= f->xsize)) {
                continue;
            }
            if(i == 0 && j == 0)
                continue;
            if((f->places[y+i][x+j] == UNKNOWN_MINE) || (f->places[y+i][x+j] == KNOWN_MINE)){
                count++;
            }
        }
    }
    return count;
}
