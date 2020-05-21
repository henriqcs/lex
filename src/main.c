#include <stdio.h>
#include "lex.h"

int
main(void)
{
	char input[LEX_INPUT_SIZE];
	while (fgets(input, LEX_INPUT_SIZE, stdin)) {
		machine(input);
	}
	return 0;
}
