######################################################################
# @author      : alex (alexbora@gmail.com)
# @file        : Makefile
# @created     : Duminică Feb 13, 2022 09:13:39 EET
######################################################################

all:
	gcc foaie_2.c -o foaie_2 -lxlsxwriter

clean:
	rm -rf *.dSYM foaie_2 play
