#include <stdio.h>
#include <cs50.h>
#include <string.h>

// Prints the given string in a +0/+1/+2 encryption loop
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error: No command-line argument.\n");
        return 1;
    }
    
    // For the string length of the second argument
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            
            // Print the first character regularly
            printf("%c", argv[1][i]);
            
            // If the character is a z or Z, print that character minus 24, mimicking a loop around
            if (argv[1][i + 1] == 'z' || argv[1][i + 1] == 'Z')
            {
                printf("%c", argv[1][i + 1] - 24);
            }
            // Otherwise, print the character after the previous character printed, one letter ahead
            else
            {
                printf("%c", argv[1][i + 1] + 1);
            }
            
            // If the character is z, Z, y, or Y, print that character minus 23, mimicking a loop around
            if (argv[1][i + 2] == 'z' || argv[1][i + 2] == 'Z' || argv[1][i + 2] == 'y' || argv[1][i + 2] == 'Y')
            {
                printf("%c", argv[1][i + 2] - 23);
            }
            
            // Otherwise, print the character that is two characters in front of the original, two letters ahead
            // Has a strange bug that causes a certain string length to make issues at the end here, but I can't seem to run debub50 to check what's happening under the hood and make a fix
            else
            {
                printf("%c3", argv[1][i + 2] + 2);
            }
            
            // Moves i up by two, so it doesn't iterate over what the previous if, else functions dealt with
            i = i + 2;
        }
    printf("\n");
    return 0;
}
