#include "main.h"
/**
* largest_number - returns the largest of 3 numbers
* @a=i: first integer
* @b=j: second integer
* @c=k: third integer
* Return: largest number
*/
int largest_number(int i, int j, int k)
{

	int largest;

	if (i > j && i > k)

	{

		largest = i;

	}

	else if (i > j && k > i)

	{

		largest = k;

	}

	else if (j > k)

	{

		largest = j;

	}

	else

	{

		largest = k;

	}

	return (largest);

	}
