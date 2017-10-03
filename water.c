#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asks for minutes showered
    printf("Minutes: ");
    int m = get_int();
    
    // Prints how many bottles of water were used in this time, the number multiplied predetermined by a given formula
    printf("Bottles: %i\n", m * 12);
}
