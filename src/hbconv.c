#include <stdio.h>

#define ARG_COUNT 2

int main ( int argc, char const *argv[] )
{
	if ( ARG_COUNT != argc ) return -1; 
	return 0;
}