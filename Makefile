######################################################################
# @author      : alex (alexbora@gmail.com)
# @file        : Makefile
# @created     : Duminică Feb 13, 2022 09:13:39 EET
######################################################################

all: 
	@./compiles.sh
	@gcc foaie_2.c -o foaie_2 `pkg-config --cflags --libs xlsxwriter`
	@echo "compiling..."
clean:
	@rm -rf *.dSYM foaie_2 parse_holidays play *.xlsx
	@echo "cleaned."
