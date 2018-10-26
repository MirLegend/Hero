LIB =	helper

SRCS =				\
	debug_helper		\
	debug_option		\
	eventhistory_stats	\
	script_loglevel		\
	sys_info		\
	watch_pools		\
	watcher

ifndef KBE_ROOT
export KBE_ROOT := $(subst /src/lib/$(LIB),,$(CURDIR))
endif

ifndef NO_USE_LOG4CXX
	NO_USE_LOG4CXX = 0
	CPPFLAGS += -DLOG4CXX_STATIC
endif

include $(KBE_ROOT)/src/build/common.mak