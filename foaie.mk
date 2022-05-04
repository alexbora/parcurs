# make -f foaie.mk


PROGRAM = foaie_2
FILES.c = net.c date.c mix.c excel.c main.c
FILES.h = date.h config.h excel.h main.h
FILES.o = ${FILES.c:.c=.o}

CC      = gcc #/opt/local/libexec/llvm-14/bin/clang
SFLAGS  = -std=c11 -D_POSIX_C_SOURCE=200112L -DSkipmain #-DLOG#-ansi -std=gnu99
GFLAGS  = -g
OFLAGS  = -O3
WFLAG1  = -Wall
WFLAG2  = -Wextra
WFLAG3  = #-Werror
WFLAG4  = # -Wstrict-prototypes
WFLAG5  = #-Wmissing-prototypes
WFLAG6	= #-Weverything -Wno-declaration-after-statement
WFLAGS  = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5} ${WFLAG6}
UFLAGS  = # Set on command line only

CFLAGS  = ${SFLAGS} ${GFLAGS} ${OFLAGS} ${WFLAGS} ${UFLAGS}
LDFLAGS =  `pkg-config --cflags --libs openssl` `pkg-config --cflags --libs xlsxwriter` 
LDLIBS  = 

all: ${PROGRAM}

${PROGRAM}: ${FILES.o}
	./compiles.sh
	${CC} -o $@ ${CFLAGS} ${FILES.o} ${LDFLAGS} ${LDLIBS}

date.o: ${FILES.h}
main.o: ${FILES.h}
# file2.o: ${FILES.h}

# If it exists, prog1.dSYM is a directory on macOS
DEBRIS = a.out core *~ *.dSYM *.o
RM_FR  = rm -fr

clean:
	${RM_FR} ${FILES.o} ${PROGRAM} ${DEBRIS}


