######################################################################
# @author      : alex (alexbora@gmail.com)
# @file        : Makefile
# @created     : Joi Iul 07, 2022 08:07:06 EEST
######################################################################

IDIR =./include
CC=gcc-12 -std=c11 -O3 -Wall -g
CFLAGS=-I$(IDIR)

ODIR=obj

LIBS=`pkg-config --cflags --libs openssl xlsxwriter` 

_OBJ = main.o sha1.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) 

main: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) test.S test1.o


.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o *.dSYM main  affinity mac_affinity sha256

