#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lex.h"
#include "string_list.h"

/*
 * General structure for a state:
 *
 * act(action, c);
 * c = input[cursor];
 * action = <N>;
 * cursor++; // if *input[cursor]* has been processed by this state.
 * goto e<N>;
 *
 */
void
machine(const char *input)
{
	char c;
	int cursor = 0;
	int action = 0;

	goto e0;

rejeita:
	printf("\nInput rejeitado\n");
	exit(EXIT_FAILURE);

e0:
	act(action, c);
	c = input[cursor];
	if (c == '\0') {
		return;
	} else if (isalpha(c)) {
		action = 1;
		cursor++;
		goto e1;
	} else if (isspace(c) && c != '\n') {
		action = 0;
		cursor++;
		goto e0;
	} else if (isdigit(c)) {
		action = 4;
		cursor++;
		goto e2;
	} else if (c == '%') {
		action = 0;
		cursor++;
		goto e6;
	} else if (ispunct(c)) {
		action = 9;
		cursor++;
		goto e5;
	} else if (c == '\n') {
		printf("\n");
		return;
	} else { /* NOTREACHED */
		goto rejeita;
	}

e1:
	act(action, c);
	c = input[cursor];
	if (isalnum(c)) {
		action = 2;
		cursor++;
		goto e1;
	} else {
		action = 3;
		goto e0;
	}

e2:
	act(action, c);
	c = input[cursor];
	if (isdigit(c)) {
		action = 5;
		cursor++;
		goto e2;
	} else {
		action = 6;
		goto e0;
	}

e5:
	act(action, c);
	c = input[cursor];
	action = 10;
	goto e0;

e6:
	act(action, c);
	c = input[cursor];
	action = 0;
	while (input[cursor] != '\n' && input[cursor] != '\0')
		cursor++;
	goto e0;
}

/*
 * The FSM changes it's state and only then act.
 * The action is performed based on the character from previous state.
 */
static void
act(int action, char c)
{
	int entry;
	char *strend;
	static char tempS[LEX_INPUT_SIZE] = "";
	static char tempC;
	static int tempN;
	static StringList tabv = NULL;
	static StringList tabp = NULL;

	if (action == 0) return;
	if (tabv == NULL) {
		tabv = sl_new();
	}
	if (tabp == NULL) {
		tabp = sl_new();
		sl_add_entry(tabp, "IF");
		sl_add_entry(tabp, "THEN");
		sl_add_entry(tabp, "ELSE");
		sl_add_entry(tabp, "GOTO");
		sl_add_entry(tabp, "LET");
		sl_add_entry(tabp, "END");
		sl_add_entry(tabp, "PRINT");
		sl_add_entry(tabp, "READ");
		sl_add_entry(tabp, "OF");
	}

	switch (action) {
	case 1:
		tempS[0] = c;
		tempS[1] = '\0';
		break;
	case 2:
		strend = strchr(tempS, '\0');
		*strend = c;
		*(strend + 1) = '\0';
		break;
	case 3:
		entry = sl_entry(tabp, tempS);
		if (entry != -1) {
			printf("P(%d)", entry);
		} else {
			entry = sl_entry(tabv, tempS);
			if (entry == -1) {
				sl_add_entry(tabv, tempS);
				entry = sl_size(tabv) - 1;
			}
			printf("V(%d)", entry);
		}
		break;
	case 4:
		tempN = (c - '0');
		break;
	case 5:
		tempN = tempN * 10 + (c - '0');
		break;
	case 6:
		printf("N(%d)", tempN);
		break;
	case 9:
		tempC = c;
		break;
	case 10:
		printf("%c", tempC);
		break;
	}
}
