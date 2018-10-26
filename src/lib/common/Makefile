LIB =	common

SRCS =				\
	blowfish		\
	common			\
	format			\
	tasks			\
	timer			\
	timestamp		\
	strutil			\
	kbeversion		\
	kbekey			\
	md5			\
	sha1			\
	base64			\
	rsa			\
	memorystream

ifndef KBE_ROOT
export KBE_ROOT := $(subst /src/lib/$(LIB),,$(CURDIR))
endif

include $(KBE_ROOT)/src/build/common.mak