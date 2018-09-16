// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com

#ifndef KBE_PY_GC_H
#define KBE_PY_GC_H

#include "common/common.h"
#include "scriptobject.h"

namespace KBEngine{ namespace script{

class PyGC
{						
public:	
	static uint32 DEBUG_STATS;
	static uint32 DEBUG_COLLECTABLE;
	static uint32 DEBUG_UNCOLLECTABLE;
	static uint32 DEBUG_SAVEALL;
	static uint32 DEBUG_LEAK;
	
	/** 
		��ʼ��pickler 
	*/
	static bool initialize(void);
	static void finalise(void);
	
	/** 
		ǿ�ƻ�������
	*/
	static void collect(int8 generations = -1);

	/** 
		���õ��Ա�־
	*/
	static void set_debug(uint32 flags);
	
	/**
		���Ӽ���
	*/
	static void incTracing(std::string name);

	/**
		���ټ���
	*/
	static void decTracing(std::string name);

	/**
		debug׷��kbe��װ��py�������
	*/
	static void debugTracing(bool shuttingdown = true);

	/**
		�ű�����
	*/
	static PyObject* __py_debugTracing(PyObject* self, PyObject* args);

private:
	static PyObject* collectMethod_;							// cPicket.dumps����ָ��
	static PyObject* set_debugMethod_;							// cPicket.loads����ָ��

	static bool	isInit;											// �Ƿ��Ѿ�����ʼ��

	static KBEUnordered_map<std::string, int> tracingCountMap_;	// ׷���ض��Ķ��������
} ;

}
}

#endif // KBE_PY_GC_H
