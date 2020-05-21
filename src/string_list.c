#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_list.h"

struct StringList {
	int size;
	char entries[LIST_SIZE][STRING_SIZE];
};

StringList
sl_new()
{
	StringList sl;
	sl = (StringList) malloc(sizeof(struct StringList));
	sl->size = 0;
	return sl;
}

int
sl_entry(StringList sl, const char *string)
{
	int i;
	for (i = 0; i < sl->size; i++)
		if (strcmp(sl->entries[i], string) == 0)
			return i;

	return -1;
}

void
sl_add_entry(StringList sl, const char *string)
{
	strcpy(sl->entries[sl->size], string);
	sl->size++;
}

void
sl_ls(StringList sl)
{
	int i;
	for (i = 0; i < sl->size; i++)
		printf("V(%d) = %s\n", i, sl->entries[i]);
}

int
sl_size(StringList sl)
{
	return sl->size;
}
