#!/usr/bin/env sh

######################################################################
# @author      : alex (alex@mac.local)
# @file        : compiles
# @created     : Thursday Mar 04, 2021 21:52:27 EET
#
# @description : 
######################################################################

# set -x
set -e

rm -rf config.h
touch config.h


compiles (){
	stage="$(mktemp -d)"
	echo "$2" > "$stage/test.c"
	(gcc-11 -Werror "$1" -o "$stage/test" "$stage/test.c" >/dev/null 2>&1)
	cc_success=$?
	rm -rf "$stage"
	return $cc_success
}


if compiles "" "
	#include <stdint.h>
	#include <stdlib.h>
	int main(void)
	{
		void (*p)(void *, size_t) = arc4random_buf;
		return (intptr_t)p;
	}";
then
  echo "#define HAVE_ARC4RANDOM 1" >> config.h 
fi

if compiles "-D_POSIX_C_SOURCE=200112L" "
	#include <stdint.h>
	#include <sys/types.h>
	#include <sys/random.h>
	int main(void)
	{
		ssize_t (*p)(void *, size_t, unsigned int) = getrandom;
		return (intptr_t)p;
	}";
then
  echo "#define HAVE_GETRANDOM 1" >> config.h
fi

if test -c /dev/random; then
  echo "#define HAVE_DEVRANDOM 1" >> config.h
fi



ls3() {
        echo "#include <openssl/rand.h>
       	int main(void){
	
	unsigned char bytes[128];
  	RAND_bytes(bytes, sizeof(bytes));
  	uint64_t res = *(uint64_t *)bytes;
  	return res % RAND_MAX;}" > test5.c
	gcc-11 -lssl -lcrypto test5.c
	rm -rf test5.c
}

if ls3;
then
	echo "#define HAVE_OPENSSL 1" >> config.h
fi

# echo $(gcc-11 --version)
