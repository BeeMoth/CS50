/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // Defines an integer equal to the dimensions of the board times itself, minus 1. Used to number tiles
    int f = (d * d) - 1;
    
    // For the amount of rows in the array
    for (int i = 0; i < d; i++)
    {
        
        // For the amount of collums in the array, set each element equal to f, lowering the value of f by 1 each time
        for (int j = 0; j < d; j++)
        {
            board[i][j] = f;
            f--;
        }
    }
    
    // If the board has an odd number of tiles, replace the last two tiles to be in the opposite order, so the game is still winnable
    // Doesn't touch the last element in the array, as that makes it default to 0
    if (d == 4 || d == 6 || d == 8)
    {
        board[d - 1][d - 3] = 1;
        board[d - 1][d - 2] = 2;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    
    // For the amount of rows
    for (int i = 0; i < d; i++)
    {
        
        // Prints the initial line for each row
        printf("|");
        
        // For each column
        for (int j = 0; j < d; j++)
        {
            
            // If the element is 0, print a blank space
            if (board[i][j] == 0)
            {
                printf("  _ |");
            }
            
            // Otherwise, print the assigned element
            // %2i ensures that the spacing is equal for double and single digit numbers
            else
            {
                printf(" %2i |", board[i][j]);
            }
        }
        
        // Move to the next row
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{

    // Define integers row and col to be used for exchanging tile spaces
    int row = 0;
    int col = 0;
    
    // For each column in each row, check to see if the value equals the given tile. If yes, assign those values to row and col
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                row = i;
                col = j;
            }
        }
    }
    
    // Looks around the given tile to see if it's within bounds and beside the blank space, the functions seperated as to not confuse where to switch. If yes, swap places with the blank space and return true
    if (row - 1 >= 0 && board[row - 1][col] == 0)
    {
        board[row - 1][col] = board[row][col];
        board[row][col] = 0;
        return true;
    }
    else if (row + 1 < d && board[row + 1][col] == 0)
    {
        board[row + 1][col] = board[row][col];
        board[row][col] = 0;
        return true;
    }
    else if (col - 1 >= 0 && board[row][col - 1] == 0)
    {
        board[row][col - 1] = board[row][col];
        board[row][col] = 0;
        return true;
    }
    else if (col - 1 < d && board[row][col + 1] == 0)
    {
        board[row][col + 1] = board[row][col];
        board[row][col] = 0;
        return true;
    }
    
    // Otherwise, return false
    else
    {
        return false;
    }
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    
    // Defines an integer meant to check whether each tile is in order or not, starting from the smallest number
    int check = 1;
    
    // For each row and column, check to see if the tile is equal to what it should be, check increasing by one every time to assess the next tile
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == check)
            {
                check++;
                
                // If check equals the dimensions times each other, return true, as that means every tile is in place and the game is won
                if (check == (d * d))
                {
                    return true;
                }
            }
            
            // Otherwise, return false
            else
            {
                return false;
            }
        }
    }
    
    // In case something goes wrong in this function for any reason, return false
    return false;
}
