#include <hbconv.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main ( void )
{
	char test_data[][17] = {
		{"5"},
		{"42"},
		{"78a"},
		{"d34b"},
		{"08e49"},
		{"3b4d82"},
		{"d4befb4"},
		{"b5c995c1"},
		{"7c9f5a8a4"},
		{"273aca398e1"},
		{"31f1f458e441"},
		{"b8bbc35ef21fd"},
		{"2fc75b8954e8df"},
		{"7b69666116c332ac"}
	};

	char test_data_answers[][13] = {
		{"BQ=="},
		{"Qg=="},
		{"B4o="},
		{"00s="},
		{"AI5J"},
		{"O02C"},
		{"DUvvtA=="},
		{"tcmVwQ=="},
		{"B8n1qKQ="},
		{"AnOso5jh"},
		{"MfH0WORB"},
		{"C4u8Ne8h/Q=="},
		{"L8dbiVTo3w=="},
		{"e2lmYRbDMqw="}
	};

	size_t string_counter = 0;
	size_t string_count = sizeof(test_data) / sizeof(*test_data);
	char* tmp_buffer = NULL;

	while ( string_counter < string_count )
	{
		tmp_buffer = convhextobase64( test_data[string_counter] );
		assert( 0 == strcmp( tmp_buffer, test_data_answers[string_counter] ) );
		free(tmp_buffer);
		string_counter++;
	}

	return 0;
}