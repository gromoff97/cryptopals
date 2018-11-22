#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARG_COUNT 2
#define HEX_SYMB_BUFFER "0123456789ABCDEFabcdef"
#define BIN_SYMB_BUFFER "01"
#define BASE64_SYMB_BUFFER "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define HEX_BLOCK_SIZE 6
#define SIX_BLOCK_SIZE 6
#define HEX_SIZE 4
#define BIN_BLOCK_SIZE ( HEX_BLOCK_SIZE * HEX_SIZE )

typedef enum cl_read_status {
	READ_OK = 0,
	READ_INVALID_COUNT,
	READ_INVALID_INPUT
} cl_read_status;

static int is_str_hex( const char* );
cl_read_status validate_arg( int, const char* );

static char* chrhextobin( char );
static int is_str_bin( const char* );
static char get_bchr_from_sextet( const char* );

static char* strhextobin( const char* );
static char* strbinblocktobase64( const char* );
static char* strbintobase64( const char* );

char* convhextobase64( const char* );

int main ( int argc, char const *argv[] )
{
	char* bin_buffer;
	char* base64_buffer;

	switch( validate_arg( argc, argv[1] ) )
	{
		case READ_INVALID_COUNT : fprintf( stderr, "hbconv : Argument count is invalid.\n" ); return -1;
		case READ_INVALID_INPUT : fprintf( stderr, "hbconv : Input is invalid.\n" ); return -2;
		case READ_OK : break;
	}

	bin_buffer = strhextobin(argv[1]);
	base64_buffer = strbintobase64(bin_buffer);

	puts(base64_buffer);

	free(base64_buffer);
	free(bin_buffer);

	return 0;
}


static int is_str_hex( const char* buffer )
{
	if ( NULL == buffer ) return -1;
	if ( 0 == strlen( buffer ) ) return -2;
	if ( 0 == buffer[ strspn( buffer, HEX_SYMB_BUFFER ) ] ) return 0;
	return -3;
}

cl_read_status validate_arg( int argument_count, const char* input_buffer )
{
	if ( ARG_COUNT != argument_count ) return READ_INVALID_COUNT;
	if ( NULL == input_buffer || 0 != is_str_hex( input_buffer ) )
		return READ_INVALID_INPUT;
	return READ_OK;
}

static char* chrhextobin( char hex_symbol )
{
	char* bin_code = malloc( sizeof(char) * ( HEX_SIZE + 1 ) );

	if ( NULL == strchr( HEX_SYMB_BUFFER, hex_symbol ) )
		return NULL;

	switch( hex_symbol )
	{
		case '0': strcpy( bin_code,"0000" ); break;
		case '1': strcpy( bin_code,"0001" ); break;
		case '2': strcpy( bin_code,"0010" ); break;
		case '3': strcpy( bin_code,"0011" ); break;
		case '4': strcpy( bin_code,"0100" ); break;
		case '5': strcpy( bin_code,"0101" ); break;
		case '6': strcpy( bin_code,"0110" ); break;
		case '7': strcpy( bin_code,"0111" ); break;
		case '8': strcpy( bin_code,"1000" ); break;
		case '9': strcpy( bin_code,"1001" ); break;

		case 'A': strcpy( bin_code,"1010" ); break;
		case 'B': strcpy( bin_code,"1011" ); break;
		case 'C': strcpy( bin_code,"1100" ); break;
		case 'D': strcpy( bin_code,"1101" ); break;
		case 'E': strcpy( bin_code,"1110" ); break;
		case 'F': strcpy( bin_code,"1111" ); break;

		case 'a': strcpy( bin_code,"1010" ); break;
		case 'b': strcpy( bin_code,"1011" ); break;
		case 'c': strcpy( bin_code,"1100" ); break;
		case 'd': strcpy( bin_code,"1101" ); break;
		case 'e': strcpy( bin_code,"1110" ); break;
		case 'f': strcpy( bin_code,"1111" ); break;

		default :
			fprintf( stderr, "hbconv : Error(UB) during converting from hex-code to binary code.\n" );
			return NULL;
	}

	return bin_code;
}

static int is_str_bin( const char* buffer )
{
	if ( NULL == buffer ) return -1;
	if ( 0 == strlen( buffer ) ) return -2;
	if ( 0 == buffer[ strspn( buffer, BIN_SYMB_BUFFER ) ] ) return 0;
	return -3;
}

static char get_bchr_from_sextet( const char* sextet_buffer )
{
	static const char base64_symb_buffer[] = BASE64_SYMB_BUFFER;
	char tmp_buffer[SIX_BLOCK_SIZE + 1] = {0};
	size_t sextet_buffer_len;

	if ( NULL == sextet_buffer ) return '*';

	sextet_buffer_len = strlen( sextet_buffer );
	if ( sextet_buffer_len > 6 ) return '*';
	if ( 0 == sextet_buffer_len ) return '=';
	if ( 0 != is_str_bin(sextet_buffer) ) return '*';

	strcpy( tmp_buffer, sextet_buffer );
	if ( SIX_BLOCK_SIZE != sextet_buffer_len )
		memset( tmp_buffer + sextet_buffer_len, '0', sizeof(char) * ( SIX_BLOCK_SIZE - sextet_buffer_len ) );

	return base64_symb_buffer[strtoul( tmp_buffer, NULL, 2 )];
}

static char* strhextobin( const char* buffer )
{
	size_t char_count, char_counter;
	char* bin_buffer;
	char* tmp_buffer;
	if ( NULL == buffer ) return NULL;
	char_count = strlen( buffer );
	if ( 0 == char_count ) return NULL;
	if ( 0 != is_str_hex( buffer ) ) return NULL;

	bin_buffer = malloc( sizeof(char) * ( ( HEX_SIZE * char_count ) + 1 ) );
	if ( NULL == bin_buffer ) return NULL;

	for ( char_counter = 0; char_counter < char_count; char_counter++ )
	{
		tmp_buffer = chrhextobin( buffer[char_counter] );
		if ( NULL == tmp_buffer )
		{
			free(bin_buffer);
			return NULL;
		}

		strcpy( bin_buffer + ( HEX_SIZE * char_counter ), tmp_buffer );
		free(tmp_buffer);
	}

	return bin_buffer;
}

static char* strbinblocktobase64( const char* block_buffer )
{
	size_t sextet_counter, char_count;
	char sextet_buffer[SIX_BLOCK_SIZE+1];
	char new_block_buffer[BIN_BLOCK_SIZE + 1] = {0};
	char* base64_block;
	if ( NULL == block_buffer ) return NULL;
	char_count = strlen( block_buffer );
	if ( 0 == char_count || char_count < 8 || char_count > BIN_BLOCK_SIZE ) return NULL;
	if ( 0 != is_str_bin( block_buffer ) ) return NULL;

	strncpy(new_block_buffer, block_buffer, char_count);
	base64_block = malloc( sizeof(char) * 4 );
	if ( NULL == base64_block ) return NULL;
	for ( sextet_counter = 0; sextet_counter < 4; sextet_counter++ )
	{
		strncpy(sextet_buffer,&new_block_buffer[sextet_counter * SIX_BLOCK_SIZE], SIX_BLOCK_SIZE);
		base64_block[sextet_counter] = get_bchr_from_sextet(sextet_buffer);
	}

	return base64_block;
}

/* TODO : working, but still need to work on it */
static char* strbintobase64( const char* buffer )
{
	size_t char_count, chars_left_count, char_counter, blocks_count;
	char* new_buffer;
	char* tmp_buffer;
	char* base64_buffer;
	char bin_block_buffer[BIN_BLOCK_SIZE+1];
	if ( NULL == buffer ) return NULL;
	char_count = strlen( buffer );
	if ( 0 == char_count ) return NULL;
	if ( 0 != is_str_bin( buffer ) ) return NULL;

	/* 1 hex - 4 bits. For example, "101" will be "0101" */
	if ( 0 == ( char_count % HEX_SIZE ) )
		chars_left_count = 0;
	else
		chars_left_count = HEX_SIZE - ( char_count % HEX_SIZE );
	/* count of hex must not be uneven. "1010 1110" will be "0000 1010 1110" */
	chars_left_count += ( ( ( chars_left_count + char_count ) / HEX_SIZE ) % 2 ) * HEX_SIZE;
	/* as a result, for example, "110" will become "0000 0110" */

	/* updating char_count */
	char_count = char_count + chars_left_count;
	new_buffer = malloc( sizeof(char) * ( char_count + 1 ) );
	if ( NULL == new_buffer ) return NULL;
	memset( new_buffer, '0', chars_left_count );
	strcpy( new_buffer + chars_left_count, buffer );

	blocks_count = ( char_count / BIN_BLOCK_SIZE );
	if ( 0 != ( char_count % BIN_BLOCK_SIZE ) )
		blocks_count++;

	base64_buffer = malloc( sizeof(char) * ( BIN_BLOCK_SIZE / SIX_BLOCK_SIZE ) * blocks_count );
	for ( char_counter = 0; char_counter < char_count; char_counter += BIN_BLOCK_SIZE )
	{
		memset( bin_block_buffer , 0, sizeof(bin_block_buffer) );

		/* if it's last block*/
		if ( ( char_counter + BIN_BLOCK_SIZE ) > char_count )
			strncpy( bin_block_buffer, new_buffer + char_counter, char_count - char_counter );
		else
			strncpy( bin_block_buffer, new_buffer + char_counter, BIN_BLOCK_SIZE );

		tmp_buffer = strbinblocktobase64(bin_block_buffer);
		strcpy(base64_buffer + (char_counter / SIX_BLOCK_SIZE), tmp_buffer);
		free(tmp_buffer);
	}
	free(new_buffer);
	return base64_buffer;
}

char* convhextobase64( const char* input_buffer )
{
	char* bin_buffer;
	char* base64_buffer;

	if ( NULL == input_buffer ) return NULL;
	if ( 0 == strlen(input_buffer) ) return NULL;

	bin_buffer = strhextobin(input_buffer);
	base64_buffer = strbintobase64(bin_buffer);

	free(bin_buffer);
	return base64_buffer;
}