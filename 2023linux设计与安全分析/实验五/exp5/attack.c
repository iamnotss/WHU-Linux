/*************************************************************************
    > File Name       : attack.c
 ************************************************************************/

#include <stdio.h>
int i;
int* addr;

void main(int argc, char* argv[])
{
    char buff[72] = {0};

	for (i = 0; i < 72; i++)
	{
		if (0 == argv[1][i])
		{
			break;
		}
		buff[i] = argv[1][i];
	}

	for (; i < 72;i++)
	{
		buff[i] = 0;
	}

	addr = &buff[72];
	for (i = 0;i < 10; i++)
	{
		addr[i] = buff;
	}
}

