BIN  = dbmgr
SRCS =						\
	dbmgr					\
	dbmgr_interface			\
	buffered_dbtasks		\
	dbTalbeModule			\
	dbtasks					\
	interfaces_handler		\
	sync_app_datas_handler	\
	main

SRCCC = 						\
	../../lib/proto/basedb.pb   \
	../../lib/proto/celldb.pb   \
	../../lib/proto/ldb.pb   \
	../../lib/proto/coms.pb
	
ASMS =

MY_LIBS =		\
	server		\
	network		\
	pyhal	\
	db_interface	\
	db_mysql	\
	thread
	

BUILD_TIME_FILE = main
USE_PYTHON = 1
USE_G3DMATH = 1
USE_OPENSSL = 1
USE_MYSQL = 1


ifndef NO_USE_LOG4CXX
	NO_USE_LOG4CXX = 0
	CPPFLAGS += -DLOG4CXX_STATIC
endif

#HAS_PCH = 1
CPPFLAGS += -DKBE_BASEAPPMGR

ifndef KBE_ROOT
export KBE_ROOT := $(subst /src/server/$(BIN),,$(CURDIR))
endif

include $(KBE_ROOT)/src/build/common.mak

