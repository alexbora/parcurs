#!/usr/bin/env sh

######################################################################
# @author      : alex (alex@mac.local)
# @file        : compiles
# @created     : Thursday Mar 04, 2021 21:52:27 EET
#
# @description : 
######################################################################

compiles ()
{
	stage="$(mktemp -d)"
	echo "$2" > "$stage/test.c"
	(cc -Werror "$1" -o "$stage/test" "$stage/test.c" >/dev/null 2>&1)
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
	}"
then
	# echo "CFLAGS += -DHAVE_ARC4RANDOM" >> config.mk
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
	}"
then
  echo "#deine HAVE_GETRANDOM 1" >> config.h
fi

if test -c /dev/random; then
  echo "#define HAVE_DEVRANDOM 1" >> config.h
fi

