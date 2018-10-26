LIB =	db_redis

SRCS =					\
	common				\
	db_interface_redis

ifndef KBE_ROOT
export KBE_ROOT := $(subst /src/lib/$(LIB),,$(CURDIR))
endif

include $(KBE_ROOT)/src/build/common.mak