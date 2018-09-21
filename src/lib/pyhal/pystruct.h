// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com

#ifndef KBE_SCRIPT_STRUCT_H
#define KBE_SCRIPT_STRUCT_H

#include "common/common.h"
#include "scriptobject.h"

namespace KBEngine{ namespace script{

class PyStruct
{						
public:	
	/** 
		���� struct.pack
	*/
	static std::string pack(PyObject* fmt, PyObject* args);

	/** 
		���� struct.unpack
	*/
	static PyObject* unpack(PyObject* fmt, PyObject* args);

	/** 
		��ʼ��pickler 
	*/
	static bool initialize(void);
	static void finalise(void);
	
private:
	static PyObject* pack_;									// struct.pack����ָ��
	static PyObject* unpack_;								// struct.unpack����ָ��

	static bool	isInit;										// �Ƿ��Ѿ�����ʼ��
} ;

}
}
#endif // KBE_SCRIPT_STRUCT_H
