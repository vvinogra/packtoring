#include "header.h"

int main(int argc, char **argv)
{
	if (getuid() == 0)
		initing_deamon();
	else
		printf("Usage: sudo ./daemon\n");
}