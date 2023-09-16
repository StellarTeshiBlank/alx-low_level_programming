#include <stdio.h>

/**
 * main - Prints all possible combinations of two
 * two-digit numbers.
 *
 * Return: Always 0 (Success).
 */

int main(void)
{
	int g, h;

       for (g = 0; g <= 98; g++)
       {
	       for (h = g + 1; h <= 99; h++)
	       {
		       putchar((g / 10) + '0');
		       putchar((g % 10) +'0');
		       putchar(' ');
		       putchar((h / 10) + '0');
		       putchar((h % 10) + '0');
		       if (g == 98 && h == 99)
		       continue;
		       putchar(',');
		       putchar(' ');
	       }
       }
       putchar('\n');
       return (0);
}

