#include <stdio.h>
#include <cs50.h>
#include <string.h>

// Prints the given string in a +1 encription
int main(int argc, string argv[])
{
    // If there's two command-line arguments, do this
    if (argc == 2)
    {
        // For the length of the second argument
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            // If the current character is z or Z, step back 25 so it loops around to a or A
            if (argv[1][i] == 'z' || argv[1][i] == 'Z')
            {
                printf("%c", argv[1][i] - 25);
            }
            
            // Otherwise, print the current character plus one
            else
            {
                printf("%c", argv[1][i] + 1);
            }
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Error: No command-line argument.\n");
        return 1;
    }
}

// Accidently did it a different way than asked, buy hey, it works
