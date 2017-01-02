#include <stdio.h>
#include <stdlib.h>

void die(char *s) {
    //perror(s);
    fprintf(stderr, "%s\n", s);
	exit(1);
}
