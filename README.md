# C programming

## Minesweeper

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
    unsigned int i,j;
    for(f->places[y-1]; f->places[y+1]; y++)
        for(f->places[x-1]; f->places[x+1]; x++)
            if(y < f->ysize && x < f->xsize && f->places[y][x] == UNKNOWN_MINE)
                count++;
    return count;
}
