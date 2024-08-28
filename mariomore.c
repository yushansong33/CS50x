#include<stdio.h>
#include<cs50.h>

void space(int a);
void brick(int b);

int main(void)
{
    int h;
    // Prompt for users to enter positive heights
    do
    {
        h = get_int("Heights? ");
    }
    while (h < 1);

    // Print bricks
    for (int n = 1; n < h + 1; n++)
    {
        space (h-n);
        brick (n);
        printf("  ");
        brick (n);
        printf("\n");
    }
}


void space(int a)
{
    for (int i = 0; i < a; i++)
    {
        printf(" ");
    }
}

void brick(int b)
{
    for (int j = 0; j < b; j++)
    {
        printf("#");
    }
}
