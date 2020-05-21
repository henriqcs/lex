#ifndef STRING_LIST_H_
#define STRING_LIST_H_

#define LIST_SIZE 80
#define STRING_SIZE 80

/* Opaque struct */
typedef struct StringList * StringList;

StringList sl_new(void);
int sl_entry(StringList sl, const char *string);
void sl_add_entry(StringList sl, const char *string);
void sl_ls(StringList sl);
int sl_size(StringList sl);

#endif
