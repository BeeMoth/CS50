#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Prints the initials of a given name in upper case
int main(void)
{
    string s = get_string();
    
    if (s != NULL);
    {
        int i = 0;
        
        // While there's a space, move on to the next character
        while(s[i] == ' ')
        {
            i++;
        }
        
        // Print the current character capitalized
        printf("%c", toupper(s[i]));
        
        // Starting where we left off, go for the length of the string
        for (int j = i, n = strlen(s); j < n; j++)
        {
            
            // If not at the first character and not at a space, print the next character capitalized
            if (j > 0 && s[j] == ' ')
            {
                printf("%c", toupper(s[j+1]));
            }
        }
    }
    printf("\n");
}

// Need to remember that these are all basically logic puzzles. There's no extra element I'm missing. It's all about using what you have creatively to achive a certain goal
