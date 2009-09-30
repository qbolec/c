#include <stdio.h>

#include <ctype.h>

char * RemoveSpaces(char * source){

	char * dest, * ret = dest = source;

	while( *(isspace(*source) ? dest : dest++) = *source++ );

	return ret;

}

main(int argc, char ** argv){  /*For testing the above.*/

	while( *(++argv) ) printf("%s", RemoveSpaces(*argv));

}
