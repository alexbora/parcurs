HOST=$(shell hostname)

CC:=gcc-12

all:
	@echo $(HOST)
	@echo $(CC)
	@whereis $(CC)
	# @which $(CC)

ifeq ($(HOST),  mac.local)
	@echo $(HOST)
@CC=gcc-12
else
@CC=gcc-10.1
endif
