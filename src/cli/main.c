#include "header.h"

int main(int argc, char *argv[])
{
	validation(argc, argv);
	system("leaks -s packtoring");
	return 0;
}