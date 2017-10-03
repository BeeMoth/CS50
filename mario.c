#include <stdio.h>
#include <cs50.h>

// Gets the desired height for the pyramid
int get_height(void)
{
    int n;
    do
    {
        printf("Height: ");
        n = get_int();
    }
    while(n < 0 || n > 23);
    return n;
}

// Prints a pyramid like the ones in Mario depending on a given height
int main(void)
{
    // Uses the given height to determine how tall the pyramid will be
    int h = get_height();
    for (int i = 0; i < h; i++)
    {
        // Minuses the row number from how many spaces are placed, as with every row, there are less spaces
        int w = h - i;
        for (int z = 0; z < w; z++)
        {
            printf(" ");
        }
        
        // Fixes issue where no # was appearing on the first row
        int g = i + 1;
        
        // Prints an amount of #s according to which row we're on
        for (int k = 0; k < g; k++)
        {
            printf("#");
        }
        
        // Prints the spaces between half-pyramids
        printf("  ");
        
        // Prints the second side of the pyramid, making a new line for the next row
        for (int k = 0; k < g; k++)
        {
            printf("#");
        }
        printf("\n");
   }
}
