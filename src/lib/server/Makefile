LIB =	server

SRCS =				\
	common			\
	components		\
	component_active_report_handler \
	entity_app		\
	forward_messagebuffer	\
	globaldata_server	\
	idallocate		\
	pendingLoginmgr		\
	serverapp		\
	serverconfig		\
	machine_infos		\
	shutdowner		\
	signal_handler

ifndef KBE_ROOT
export KBE_ROOT := $(subst /src/lib/$(LIB),,$(CURDIR))
endif

USE_PYTHON=1
USE_JWSMTP = 1

ifndef NO_USE_LOG4CXX
	NO_USE_LOG4CXX = 0
	CPPFLAGS += -DLOG4CXX_STATIC
endif

include $(KBE_ROOT)/src/build/common.mak