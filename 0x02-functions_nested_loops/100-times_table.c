#include "main.h"
/**
 * print_times_table - Prints the n times table
 *
 * @n: number times table (0 < n <= 15)
 *
 * Return: no return
 */
void print_times_table(int n)
{
	int a, b, op;

	if (n >= 0 && n <= 15)
	{
		for (a = 0; a <= n; a++)
		{
			_putchar(48);
			for (b = 1; b <= n; b++)
			{
				op = a * b;
				_putchar(44);
				_putchar(32);
				if (op <= 9)
				{
					_putchar(32);
					_putchar(op / 10);
					_putchar(op % 10);
				}
				else if (op <= 99)
				{
					_putchar(32);
					_putchar(op / 10);
					_putchar(op % 10);
				}
				else
				{
					_putchar((op / 100) % 10);
					_putchar((op / 10) % 10);
					_putchar(op % 10);
				}
			}
			_putchar('\n');
		}
	}
}
