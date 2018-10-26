LIB =	pyhal

SRCS =				\
	copy			\
	install_py_dlls		\
	map			\
	math			\
	pickler			\
	py_gc			\
	pystruct		\
	pyprofile		\
	pyprofile_handler	\
	py_memorystream		\
	pywatcher		\
	script			\
	scriptobject		\
	scriptstdout		\
	scriptstderr		\
	scriptstdouterr		\
	scriptstdouterrhook	\
	sequence		

ifndef KBE_ROOT
export KBE_ROOT := $(subst /src/lib/$(LIB),,$(CURDIR))
endif

USE_PYTHON=1
USE_G3DMATH=1
include $(KBE_ROOT)/src/build/common.mak