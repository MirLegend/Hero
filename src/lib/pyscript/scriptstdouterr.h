// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com

#ifndef KBE_SCRIPTSTDOUTERR_H
#define KBE_SCRIPTSTDOUTERR_H

#include "helper/debug_helper.h"
#include "common/common.h"
#include "scriptobject.h"
#include "scriptstdout.h"
#include "scriptstderr.h"

namespace KBEngine{ namespace script{
class ScriptStdOutErr
{					
public:	
	ScriptStdOutErr();
	virtual ~ScriptStdOutErr();

	/** 
		��װ��ж�����ģ�� 
	*/
	bool install(void);
	bool uninstall(void);
	bool isInstall(void) const{ return isInstall_; }

	virtual void error_msg(const wchar_t* msg, uint32 msglen);
	virtual void info_msg(const wchar_t* msg, uint32 msglen);

	void pyPrint(const std::string& str);

	INLINE std::wstring& buffer();

protected:
	ScriptStdErr* pStderr_;
	ScriptStdOut* pStdout_;
	PyObject* pyPrint_;
	bool isInstall_;
	std::wstring sbuffer_;
} ;

}
}

#ifdef CODE_INLINE
#include "scriptstdouterr.inl"
#endif

#endif // KBE_SCRIPTSTDOUTERR_H
