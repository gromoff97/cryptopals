#include <hbconv.h>
#include <assert.h>
#include <stdlib.h>

int main ( void )
{
	char test_data[][16] = {
		{"abcdef"},
		{"01234abcd"},
		{"0"},
	};

	size_t string_counter = 0;
	size_t string_count = sizeof(test_data) / sizeof(*test_data);

	while ( string_counter < string_count )
	{
		/* assertions will be here */
		string_counter++;
	}

	return 0;
}