IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
SDIR=src

_DEPS = lex.h string_list.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o lex.o string_list.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lex: $(OBJ)
	$(CC) -o $@ $^

.PHONY: clean check

clean:
	rm -f $(ODIR)/*.o $(IDIR)/*~ *~ core

check: lex
	@test/check.sh
