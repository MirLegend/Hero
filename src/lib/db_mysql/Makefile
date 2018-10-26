LIB =	db_mysql

SRCS =					\
	common				\
	db_exception			\
	db_transaction			\
	db_interface_mysql		\
	entity_table_mysql		\
	kbe_table_mysql

USE_PYTHON = 1
USE_G3DMATH=1

ifndef KBE_ROOT
export KBE_ROOT := $(subst /src/lib/$(LIB),,$(CURDIR))
endif

include $(KBE_ROOT)/src/build/common.mak
