#include <stdio.h>
#include <cs50.h>

// Prints the lowest amount of coins possible to add up to a given amount of change
int main(void)
{
    float n;
    do
    {
        printf("How much change is owed?\n");
        n = get_float();
    }
    while(n < 0);
    
    int z = 0;
    
    while(n > 0.25)
    {
        z++;
        n = n - 0.25;
    }
    
    while(n > 0.10)
    {
        z++;
        n = n - 0.10;
    }

    while(n > 0.05)
    {
        z++;
        n = n - 0.05;
    }

    while(n > 0.01)
    {
        z++;
        n = n - 0.01;
    }
    
    printf("%i\n", z);
}
