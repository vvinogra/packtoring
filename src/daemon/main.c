#include "header.h"

int main(void)
{
	if (getuid() == 0)
		initing_deamon();
	else
		printf("Usage: sudo ./daemon\n");
}